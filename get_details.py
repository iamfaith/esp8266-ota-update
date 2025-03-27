import os
from dotenv import load_dotenv
Import("env")

# Load environment variables from .env file
load_dotenv()

ssid = os.getenv("WIFI_SSID")
password = os.getenv("WIFI_PASSWORD")

if ssid and password:
    env.Append(
        BUILD_FLAGS=[
            f"-DWIFI_SSID=\\\"{ssid}\\\"",
            f"-DWIFI_PASSWORD=\\\"{password}\\\""
        ]
    )
else:
    print("Warning: WIFI_SSID or WIFI_PASSWORD not set in .env")
