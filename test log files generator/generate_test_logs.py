import os
from datetime import datetime, timedelta
import random

# base date for generating timestamps
base_date = datetime(2023, 11, 14, 8, 30)

# components and Event Types for generating log entries
components = ["patient simulator", "insulin pump"]
events = {
    "patient simulator": [("glucose-monitor-report", "sugar-level")],
    "insulin pump": [("Start-Infusion", "infusion-amount")]
}

# generate a single log entry
def generate_log_entry(timestamp, component):
    event_type, data_field = random.choice(events[component])
    if data_field == "sugar-level":
        data_value = random.randint(100, 200)
    else:
        data_value = random.randint(5, 20)
    return f"{timestamp}, {component}, {event_type}, {data_field}, {data_value}"

# save log entries to a text file with a unique name based on the date
def save_log_file(log_entries, base_date):
    # make filename based on the base date
    date_str = base_date.strftime("%Y-%m-%d")
    file_index = 1
    file_name = f"{date_str}-{file_index}.txt"
    file_path = f'{file_name}'

    # check if the file already exists, if yes increase file index number
    while os.path.exists(file_path):
        file_index += 1
        file_name = f"{date_str}-{file_index}.txt"
        file_path = f'{file_name}'

    # writing the log entries to the file
    with open(file_path, 'w') as file:
        file.write("\n".join(log_entries))

    return file_path

# Generate 50 log entries. Can change to make more logs.
log_entries = []
for i in range(50):
    timestamp = base_date + timedelta(minutes=5 * i)
    component = random.choice(components)
    log_entry = generate_log_entry(timestamp.isoformat(), component)
    log_entries.append(log_entry)

# Save the log file
log_file_path = save_log_file(log_entries, base_date)
log_file_path