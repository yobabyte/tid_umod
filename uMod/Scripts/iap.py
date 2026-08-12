#!/usr/bin/env python3

import serial
import argparse
from struct import pack
from functools import reduce
import progressbar
import time

BLOCK_SIZE = 32
BAUD_RATE = 115200

IAP_CMD_MAGIC = (
    b"\xa0\xee\x74\x71"
    b"\x07\x74\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55"
    b"\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55"
)
# IAP_CMD_MAGIC = 0xA0 # Erase
IAP_REQ_WRITE = 0xA1
IAP_REQ_WRITE_AND_REBOOT = 0xA2

IAP_RESP_OK = 0xA5
IAP_RESP_CHECKSUM_OK = 0xA3


def chunks(data, n):
    for i in range(0, len(data), n):
        yield data[i : i + n]


def write_flash(ser1: serial.Serial, port: str, rate: int, data: bytes) -> None:
    print("Awaiting connection from the device ...")
    with serial.Serial(port, rate, timeout=3.0) as ser:
        status = ser.read_until(IAP_RESP_OK.to_bytes() * 4)
        if not any(x for x in status if x == IAP_RESP_OK):
            return False

        ser.write(IAP_CMD_MAGIC)
        time.sleep(0.15)
        status = ser.read_until(IAP_RESP_OK.to_bytes(), 4)
        if not any(x for x in status if x == IAP_RESP_OK):
            print(f"Erase operation failed ({hex(status[0])})!")
            return False

        time.sleep(0.25)
        ser.reset_input_buffer()

        num_blocks = len(data) // BLOCK_SIZE
        print(f"Writing {len(data)} bytes ...")
        pg = progressbar.ProgressBar(max_value=len(data))
        for block_num, chunk in enumerate(chunks(data, BLOCK_SIZE)):
            is_last_block = block_num == (num_blocks - 1)

            cmd = IAP_REQ_WRITE
            if is_last_block:
                cmd = IAP_REQ_WRITE_AND_REBOOT

            checksum = reduce(lambda x, y: x + y, chunk, 0) & 0xFF
            header = pack(">BHB", cmd, block_num, checksum)
            ser.write(header + chunk)

            status = ser.read(1)
            if len(status) < 1 or status[0] != IAP_RESP_CHECKSUM_OK:
                print(f"\nWrite operation failed!")
                return False

            pg.increment(len(chunk), force=is_last_block)

    return True


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        "In-App Programming Tool for 3773/3782",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    parser.add_argument("-p", "--port", type=str, default="COM3", help="COM port")
    parser.add_argument("-r", "--rate", type=int, default=BAUD_RATE, help="serial baud rate")
    parser.add_argument("-f", "--file", type=str, required=True, help="firmware file")
    parser.add_argument("-d", "--debug", type=bool)
    return parser.parse_args()


def main() -> None:
    args = parse_args()

    if args.file.lower()[-4:] == '.hex':
        with open(args.file, "r") as fw_file:
            from intelhex import IntelHex
            firmware = IntelHex(fw_file).tobinstr()
    else:
        with open(args.file, "rb") as fw_file:
            firmware = fw_file.read()

    alignment = BLOCK_SIZE - (len(firmware) % BLOCK_SIZE)
    firmware += b"\x00" * alignment

    while True:
        try:
            if write_flash(None, args.port, args.rate, firmware):
                break
        except (OSError, FileNotFoundError):
            print("Device not found!")
            break
        except KeyboardInterrupt:
            print("Interrupted ...")
            break
        except Exception as ex:
            print(f"\nExc: {ex}")


if __name__ == "__main__":
    main()
