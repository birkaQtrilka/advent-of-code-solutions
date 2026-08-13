import os
import json

CONFIG_FILE = "registry-config.json"

def load_config():
    """Loads the config file. Creates a default one if it doesn't exist."""
    if not os.path.exists(CONFIG_FILE):
        default_config = {"selected_year": 2025} # Default starting year
        save_config(default_config)
        return default_config
        
    with open(CONFIG_FILE, 'r') as f:
        return json.load(f)

def save_config(config):
    """Saves a dictionary back to the config file."""
    with open(CONFIG_FILE, 'w') as f:
        json.dump(config, f, indent=4)