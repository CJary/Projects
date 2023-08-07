import requests
import webbrowser
import tkinter as tk
from tkinter import ttk, messagebox
from ttkthemes import ThemedTk

# Read API key from a file
def read_api_key_from_file(filename):
    with open(filename, 'r') as file:
        content = file.read()

    # Extract Client ID and API Key
    client_id_start = content.find("Client ID:") + len("Client ID:")
    client_id_end = content.find("API Key:")
    api_key_start = content.find("API Key:") + len("API Key:")
    client_id = content[client_id_start:client_id_end].strip()
    api_key = content[api_key_start:].strip()

    return client_id, api_key

# Display restaurant details in a new window
def show_restaurant_details(index):
    selected_restaurant = restaurants[index]
    # Extract restaurant details
    name = selected_restaurant['name']
    rating = selected_restaurant['rating']
    review_count = selected_restaurant['review_count']
    price = selected_restaurant.get('price', 'N/A')
    address = selected_restaurant['location']['address1']
    phone = selected_restaurant['phone']
    categories = ', '.join(category['title'] for category in selected_restaurant['categories'])
    link = selected_restaurant['url']
    opening_hours = selected_restaurant['hours'][0]['open'] if 'hours' in selected_restaurant and selected_restaurant['hours'] else 'N/A'

    # Create a new window to display restaurant details
    details_window = tk.Toplevel(root)
    details_window.title(f"{name} Details")
    details_window.geometry("400x300")

    # Display restaurant details in the new window
    restaurant_details = (
        f"Name: {name}\n"
        f"Rating: {rating}\n"
        f"Review Count: {review_count}\n"
        f"Price Range: {price}\n"
        f"Address: {address}\n"
        f"Phone Number: {phone}\n"
        f"Categories: {categories}\n"
        f"Opening Hours: {opening_hours}\n"
    )

    details_label = tk.Label(details_window, text=restaurant_details, font=('Helvetica', 12))
    details_label.pack(padx=20, pady=20)

    # Add a button to open the restaurant's Yelp page in the browser
    def open_yelp_page():
        webbrowser.open(link)

    yelp_button = tk.Button(details_window, text="Open Yelp Page", command=open_yelp_page)
    yelp_button.pack(pady=10)

# Fetch restaurants from Yelp API based on user input
def get_restaurants(term, location, price, sort_by):
    url = 'https://api.yelp.com/v3/businesses/search'
    params = {
        'term': term,
        'location': location,
        'price': price,
        'sort_by': sort_by,
        'limit': 10
    }
    headers = {
        'Authorization': f'Bearer {API_KEY}'
    }
    try:
        response = requests.get(url, params=params, headers=headers)
        response.raise_for_status()
        data = response.json()
        return data.get('businesses', [])
    except requests.exceptions.HTTPError as http_err:
        print(f"HTTP error occurred: {http_err}")
    except requests.exceptions.RequestException as req_err:
        print(f"Request exception occurred: {req_err}")
    except ValueError as val_err:
        print(f"Error while parsing JSON data: {val_err}")
    return []

# Search for restaurants based on user input
def search_restaurants():
    global restaurants
    term = term_entry.get()
    location = location_entry.get()
    price = price_entry.get()
    sort_by = sort_by_var.get()

    restaurants_listbox.delete(0, tk.END)

    # Validate price input
    valid_price_ranges = ['$', '$$', '$$$', '$$$$']
    if price not in valid_price_ranges and price != '':
        messagebox.showerror("Invalid Input", "Please enter a valid price range: $, $$, $$$, $$$$")
        return

    price_map = {
        '': None,
        '$': '1',
        '$$': '2',
        '$$$': '3',
        '$$$$': '4'
    }
    price = price_map.get(price, None)

    restaurants = get_restaurants(term, location, price, 'best_match')

    # Sort restaurants based on user's selected sorting option
    if sort_by == "Rating":
        restaurants = sorted(restaurants, key=lambda x: x['rating'], reverse=True)
    elif sort_by == "Review Count":
        restaurants = sorted(restaurants, key=lambda x: x['review_count'], reverse=True)

    for index, restaurant in enumerate(restaurants):
        # Extract restaurant info
        name = restaurant['name']
        address = restaurant['location']['address1']
        opening_hours = restaurant['hours'][0]['open'] if 'hours' in restaurant and restaurant['hours'] else 'N/A'

        # Format and insert restaurant info in the listbox
        restaurant_info = (
            f"Restaurant Name: {name}  >>>"
            f"Address: {address}  >>>"
            f"Opening Hours: {opening_hours}"
        )
        unique_identifier = f"#{index + 1}"
        restaurants_listbox.insert(tk.END, unique_identifier)
        restaurants_listbox.insert(tk.END, restaurant_info)
        restaurants_listbox.insert(tk.END, '')

# Handle listbox selection event
def on_listbox_select(event):
    selected_index = restaurants_listbox.curselection()
    if selected_index:
        literal_index = int(selected_index[0])
        restaurant_index = literal_index // 3
        if literal_index % 3 == 1:
            show_restaurant_details(restaurant_index)


#Main Program
if __name__ == "__main__":
    API_KEY_FILE = 'api.txt'
    client_id, API_KEY = read_api_key_from_file(API_KEY_FILE)

    # Create the main window
    root = ThemedTk(theme="clearlooks")
    root.title('Restaurant Explore')

    # Set the window size to 800x600 pixels
    window_width = 800
    window_height = 600
    root.geometry(f"{window_width}x{window_height}")

    # Center the window on the screen
    screen_width = root.winfo_screenwidth()
    screen_height = root.winfo_screenheight()
    x_pos = (screen_width - window_width) // 2
    y_pos = (screen_height - window_height) // 2
    root.geometry(f"+{x_pos}+{y_pos}")

    # Set a background color for the window
    root.configure(bg='white')

    # Create a frame for the search input section
    search_frame = ttk.Frame(root, padding=10)
    search_frame.pack(fill=tk.BOTH, padx=10, pady=10)

    term_label = tk.Label(search_frame, text="Search Term:", font=('Helvetica', 14, 'bold'))
    term_label.grid(row=0, column=0, padx=5, pady=5, sticky=tk.W)
    term_entry = tk.Entry(search_frame, width=40, font=('Helvetica', 12))
    term_entry.grid(row=0, column=1, padx=5, pady=5)

    location_label = tk.Label(search_frame, text="Location:", font=('Helvetica', 14, 'bold'))
    location_label.grid(row=1, column=0, padx=5, pady=5, sticky=tk.W)
    location_entry = tk.Entry(search_frame, width=40, font=('Helvetica', 12))
    location_entry.grid(row=1, column=1, padx=5, pady=5)

    price_label = tk.Label(search_frame, text="Price Range (Optional):", font=('Helvetica', 14, 'bold'))
    price_label.grid(row=2, column=0, padx=5, pady=5, sticky=tk.W)
    price_entry = tk.Entry(search_frame, width=10, font=('Helvetica', 12))
    price_entry.grid(row=2, column=1, padx=5, pady=5)

    sort_by_label = tk.Label(search_frame, text="Sort by:", font=('Helvetica', 14, 'bold'))
    sort_by_label.grid(row=3, column=0, padx=5, pady=5, sticky=tk.W)

    sort_options = ["Best Match", "Rating", "Review Count", "Distance"]
    sort_by_var = tk.StringVar()
    sort_by_var.set(sort_options[0])
    sort_by_menu = ttk.OptionMenu(search_frame, sort_by_var, *sort_options)
    sort_by_menu.grid(row=3, column=1, padx=5, pady=5)

    search_button = tk.Button(search_frame, text="Search Restaurants", command=search_restaurants,
                              bg='green', fg='white', font=('Helvetica', 14, 'bold'))
    search_button.grid(row=4, column=0, columnspan=2, padx=5, pady=10)

    # Create a frame for the search results list
    results_frame = ttk.Frame(root, padding=10)
    results_frame.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)

    restaurants_listbox = tk.Listbox(results_frame, width=80, height=20, font=('Helvetica', 12))
    restaurants_listbox.pack(fill=tk.BOTH, expand=True)
    restaurants_listbox.bind('<<ListboxSelect>>', on_listbox_select)

    # Create a frame for the restaurant details display
    details_frame = ttk.Frame(root, padding=10)
    details_frame.pack(fill=tk.BOTH, padx=10, pady=10)

    details_label = tk.Label(details_frame, text="", font=('Helvetica', 12))
    details_label.pack(padx=20, pady=20)

    # Run the GUI event loop
    root.mainloop()
