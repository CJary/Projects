#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>

#include "image.h"
#include "priority_queue.h"

// ===================================================================================================

// distance field method functions
double NaiveDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image);

//function added to check bounds
bool checkBounds(int xSize, int ySize, int X, int Y, int x, int y){
    if (x == 0 && y == 0){ //if its current black
        return true;
    }
    else if (X < 0 || Y < 0){
        return true;
    }
    else if (X >= xSize || Y >= ySize){
        return true;
    }
    else{
        return false;
    }

}

// visualization style helper functions
Color Rainbow(double distance, double max_distance);
Color GreyBands(double distance, double max_distance, int num_bands);

// ===================================================================================================

int main(int argc, char* argv[]) {
  if (argc != 5) {
    std::cerr << "Usage: " << argv[0] << " input.ppm output.ppm distance_field_method visualization_style" << std::endl;
    exit(1);
  }

  // open the input image
  Image<Color> input;
  if (!input.Load(argv[1])) {
    std::cerr << "ERROR: Cannot open input file: " << argv[1] << std::endl;
    exit(1);
  }

  // a place to write the distance values
  Image<DistancePixel> distance_image;
  distance_image.Allocate(input.Width(),input.Height());

  // calculate the distance field (each function returns the maximum distance value)
  double max_distance = 0;
  if (std::string(argv[3]) == std::string("naive_method")) {
    max_distance = NaiveDistanceFieldMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("improved_method")) {
    max_distance = ImprovedDistanceFieldMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("pq_with_map")) {
    max_distance = FastMarchingMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("pq_with_hash_table")) {
    // EXTRA CREDIT: implement FastMarchingMethod with a hash table
  } else {
    std::cerr << "ERROR: Unknown distance field method: " << argv[3] << std::endl;
    exit(1);
  }

  // convert distance values to a visualization
  Image<Color> output;
  output.Allocate(input.Width(),input.Height());
  for (int i = 0; i < input.Width(); i++) {
    for (int j = 0; j < input.Height(); j++) {
      double v = distance_image.GetPixel(i,j).getValue();
      if (std::string(argv[4]) == std::string("greyscale")) {
	output.SetPixel(i,j,GreyBands(v,max_distance*1.01,1));
      } else if (std::string(argv[4]) == std::string("grey_bands")) {
	output.SetPixel(i,j,GreyBands(v,max_distance,4));
      } else if (std::string(argv[4]) == std::string("rainbow")) {
	output.SetPixel(i,j,Rainbow(v,max_distance));
      } else {
	// EXTRA CREDIT: create other visualizations
	std::cerr << "ERROR: Unknown visualization style" << std::endl;
	exit(0);
      }
    }
  }
  // save output
  if (!output.Save(argv[2])) {
    std::cerr << "ERROR: Cannot save to output file: " << argv[2] << std::endl;
    exit(1);
  }

  return 0;
}

// ===================================================================================================

double NaiveDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
  int w = input.Width();
  int h = input.Height();
  // return the maximum distance value
  double answer = 0;
  // loop over the pixels in the input image
  for (int i = 0; i < w; i++)  {
    for (int j = 0; j < h; j++) {
      double closest = -1;
      // loop over all other pixels in the input image
      for (int i2 = 0; i2 < w; i2++)  {
	for (int j2 = 0; j2 < h; j2++) {
	  const Color& c = input.GetPixel(i2,j2);
	  // skip all pixels that are not black
	  if (!c.isBlack()) continue;
	  // calculate the distance between the two pixels
	  double distance = sqrt((i-i2)*(i-i2) + (j-j2)*(j-j2));
	  // store the closest distance to a black pixel
	  if (closest < 0 || distance < closest) {
	    closest = distance;
	  }
	}
      }
      assert (closest >= 0);
      answer = std::max(answer,closest);
      // save the data to the distance image
      DistancePixel& p = distance_image.GetPixel(i,j);
      p.setValue(closest);
    }
  }
  return answer;
}


double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
    //
    // IMPLEMENT THIS FUNCTION
    //
    // a small improvement on the NaiveDistanceFieldMethod
    //

    //MAIN DIFFERENCE is getting all the location of
    //black pixel first
    int w = input.Width();
    int h = input.Height();
    // return the maximum distance value
    double answer = 0;
    // create a list of black pixel coordinates
    vector<pair<int, int> > black_pixels;
    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            Color c = input.GetPixel(x, y);
            if (c.isBlack()) {
                black_pixels.push_back(make_pair(x, y));
                distance_image.GetPixel(x, y).setValue(0.0);
            }
        }
    }

    // loop over the pixels in the input image
    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            double closest = -1;
            // calculate the distance to all black pixels
            Color c = input.GetPixel(x, y);
            if (!c.isBlack()){
                for (vector<pair<int, int> >::iterator itr = black_pixels.begin();
                     itr != black_pixels.end(); itr++) {
                    double distance = sqrt(((x - itr->first) * (x - itr->first)) +
                                           ((y - itr->second) * (y - itr->second)));
                    // store the closest distance to a black pixel
                    if (closest < 0 || distance < closest) {
                        closest = distance;
                    }
                }
            }
            //set the answer to closest
            if (closest > answer){
                answer = closest;
            }

            // save the data to the distance image
            distance_image.GetPixel(x, y).setValue(closest);
        }
    }
    return answer;
}

double FastMarchingMethod(Image<Color>& input, Image<DistancePixel>& distance_image) {
    // initialize an empty priority queue
    DistancePixel_PriorityQueue PQ;

    int w = input.Width();
    int h = input.Height();

    double answer = 0;

    // loop through all pixels and push the black ones into the priority queue
    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            Color& c = input.GetPixel(x, y);
            DistancePixel& p = distance_image.GetPixel(x, y);

            // if the pixel is black, set its value to 0 and push it to the queue
            if (c.isBlack()) {
                p.setValue(0.0);
                p.setX(x);
                p.setY(y);
                PQ.push(&p);
            }
        }
    }

    // loop until the priority queue becomes empty
    while (!PQ.empty()) {
        // access the top pixel from the priority queue
        const DistancePixel* top = PQ.top();
        answer = top->getValue();

        int x = top->getX();
        int y = top->getY();

        // remove the value from the priority queue
        PQ.pop();

        // loop through all the neighbors of the known pixel
        for (int tmpx = -1; tmpx <= 1; tmpx++) {
            for (int tmpy = -1; tmpy <= 1; tmpy++) {
                int X = x + tmpx;
                int Y = y + tmpy;

                // checks bounds
                if (checkBounds(w, h, X, Y, x, y)){
                    continue;
                }

                Color& C = input.GetPixel(X, Y);
                DistancePixel& P = distance_image.GetPixel(X, Y);

                // if the neighbor is not black and not 0, then set it to red,
                // and calculate the distance between it and the known pixel
                if (!C.isBlack() && P.getValue() != 0) {
                    double dist = sqrt((X-x) * (X-x) + (Y-y) * (Y-y)) + top->getValue();

                    // if the distance value needs to be updated, update it
                    if (P.getValue() > dist) {
                        P.setValue(dist);
                        P.setX(X);
                        P.setY(Y);

                        // if it's not in the queue yet, push it to the queue
                        if (!PQ.in_heap(&P)){
                            PQ.push(&P);
                        }
                        else{
                            PQ.update_position(&P);
                        }
                    }
                }
            }
        }
    }

    return answer;
}


// ===================================================================================================

Color Rainbow(double distance, double max_distance) {
  Color answer;
  if (distance < 0.001) {
    // black
    answer.r = 0; answer.g = 0; answer.b = 0;
  } else if (distance < 0.2*max_distance) {
    // blue -> cyan
    double tmp = distance * 5.0 / max_distance;
    answer.r = 0;
    answer.g = tmp*255;
    answer.b = 255;
  } else if (distance < 0.4*max_distance) {
    // cyan -> green
    double tmp = (distance-0.2*max_distance) * 5.0 / max_distance;
    answer.r = 0;
    answer.g = 255;
    answer.b = (1-tmp*tmp)*255;
  } else if (distance < 0.6*max_distance) {
    // green -> yellow
    double tmp = (distance-0.4*max_distance) * 5.0 / max_distance;
    answer.r = sqrt(tmp)*255;
    answer.g = 255;
    answer.b = 0;
  } else if (distance < 0.8*max_distance) {
    // yellow -> red
    double tmp = (distance-0.6*max_distance) * 5.0 / max_distance;
    answer.r = 255;
    answer.g = (1-tmp*tmp)*255;
    answer.b = 0;
  } else if (distance < max_distance) {
    // red -> white
    double tmp = (distance-0.8*max_distance) * 5.0 / max_distance;
    answer.r = 255;
    answer.g = tmp*255;
    answer.b = tmp*255;
  } else {
    // white
    answer.r = answer.g = answer.b = 255;
  }
  return answer;
}

Color GreyBands(double distance, double max_value, int num_bands) {
  Color answer;
  if (distance < 0.001) {
    // red
    answer.r = 255; answer.g = 0; answer.b = 0;
  } else {
    // shades of grey
    answer.r = answer.g = answer.b = int(num_bands*256*distance/double(max_value)) % 256;
  }
  return answer;
}

// ===================================================================================================
