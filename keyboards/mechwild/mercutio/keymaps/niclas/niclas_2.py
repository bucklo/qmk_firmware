import sys
import hid

vendor_id     = 0x1337
product_id    = 0x7331

usage_page    = 0xFF60
usage         = 0x61
report_length = 32

def get_raw_hid_interface():
    device_interfaces = hid.enumerate(vendor_id, product_id)
    raw_hid_interfaces = [i for i in device_interfaces if i['usage_page'] == usage_page and i['usage'] == usage]

    if len(raw_hid_interfaces) == 0:
        return None

    interface = hid.device()
    interface.open_path(raw_hid_interfaces[0]['path'])

    print(f"Manufacturer: {interface.get_manufacturer_string()}")
    print(f"Product: {interface.get_product_string()}")

    return interface

def send_raw_report():
    interface = get_raw_hid_interface()

    if interface is None:
        print("No device found")
        sys.exit(1)

    user_input = input("Enter a string to send: ")
    user_input = '\0' + user_input
    data = [ord(char) for char in user_input]

    request_data = [0x00] * (report_length + 1)  # First byte is Report ID
    request_data[1:len(data) + 1] = data
    print(request_data)
    request_report = bytes(request_data)

    print("Request:")
    print(request_report)

    try:
        interface.write(request_report)
#        response_report = interface.read(report_length, timeout=1000)

 #       print("Response:")
 #       print(response_report)
    finally:
        interface.close()

if __name__ == '__main__':
    send_raw_report()
