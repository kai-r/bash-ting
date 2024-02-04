#!/bin/bash

python3 <<EOF
import requests
from bs4 import BeautifulSoup
import csv
from datetime import datetime

# Function to fetch HTML content from the URL
def get_html_content(url):
    response = requests.get(url)
    return response.text

# Function to extract location name and current temperature from HTML
def extract_info(html_content):
    soup = BeautifulSoup(html_content, 'html.parser')

    # Extracting location name
    location_name = soup.find('h1', class_='location-name').text.strip()

    # Extracting current temperature
    temperature_element = soup.find('span', class_='temperature')
    current_temperature = temperature_element.text.strip() if temperature_element else None

    return location_name, current_temperature

# Function to write data to CSV file
def write_to_csv(time, location, degree):
    with open('temperature_data.csv', 'a', newline='') as csvfile:
        csv_writer = csv.writer(csvfile)
        csv_writer.writerow([time, location, degree])

# URL of the website
url = "https://www.yr.no/en/content/1-107212/card.html?mode=dark"

# Fetch HTML content
html_content = get_html_content(url)

# Extract information
location_name, current_temperature = extract_info(html_content)

# Get the current time
current_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

# Print the information
print("Time:", current_time)
print("Location:", location_name)
print("Current Temperature:", current_temperature, "°C")
# Write to CSV file
write_to_csv(current_time, location_name, current_temperature)
EOF
