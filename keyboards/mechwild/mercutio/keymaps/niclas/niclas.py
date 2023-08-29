import hid

# Your device's VID and PID
VID = 0x1337 # REPLACE ME NICLAS
PID = 0x1337 # REPLACE ME NICLAS

print(f"Searching for device with VID={VID} PID={PID}")

# Find your device by VID and PID
for d in hid.enumerate():
    keys = list(d.keys())
    if d['vendor_id'] == YOUR_VID and d['product_id'] == YOUR_PID:
        path = d['path']
        print(f"Found device at {path}")
        break
else:
    raise ValueError('Device not found')

# Connect to the device
device = hid.device()
device.open_path(path)

# Construct the packet
packet = bytearray(32)  # Assuming packet size of 32 bytes
packet[0] = 0x01  # Custom command identifier
packet[1:8] = "testing".encode('utf-8')  # The message, fits in 7 bytes

# Send the packet
print(f"Sending packet: {packet}")
device.write(packet)
