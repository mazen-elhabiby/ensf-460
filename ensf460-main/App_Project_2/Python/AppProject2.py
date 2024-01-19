"""
Group:  Group 20
Author: Maged El Habiby, Mazen El Habiby, Marshal kalynchuk
file:   AppProject2.py
"""
import serial
import time
import pandas as pd
import matplotlib.pyplot as plt

# Constants for ADC conversion
PWM_MAX = 65536  # Assume a 10-bit ADC


def initialize_serial_connection(port, baudrate):
    """ Initialize and return a serial connection. """
    return serial.Serial(port=port, baudrate=baudrate, bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE)

def save_data_to_csv(df, filename):
    """ Save the DataFrame to a CSV file. """
    df.to_csv(filename, index=False)

def read_serial_data(ser,duration):
    """Reads data from serial port."""
    start_time = time.time()
    data_points = []

    try:
        while start_time + duration > time.time():
            line = ser.readline()
            if line:
                timestamp = time.time() - start_time
                data_point = line.decode('utf-8', errors='replace').strip()
                data_points.append({'Time': timestamp, 'PWM Value': data_point})
            else:
                time.sleep(0.01)
    except serial.SerialException as e:
        print(f"Serial error: {e}")
    except Exception as e:
        print(f"General error: {e}")

    if not data_points:
        print("No data received.")
    
    return pd.DataFrame(data_points)

def plot_data(df):
    """ Plot intensity and voltage over time. """
    plt.figure(figsize=(10, 6))
    plt.subplot(2, 1, 1)
    plt.plot(df['Time'], df['Intensity'], label='LED Intensity')
    plt.xlabel('Time (s)')
    plt.ylabel('Intensity')
    plt.title('LED Intensity Over Time')
    plt.legend()

    plt.subplot(2, 1, 2)
    plt.plot(df['Time'], df['PWM Value'], label='PWM Value')
    plt.xlabel('Time (s)')
    plt.ylabel('PWM Value (V)')
    plt.title('PWM Output Over Time')
    plt.legend()

    plt.tight_layout()
    plt.show()

def process_data(df):
    """ Process the DataFrame to calculate voltage and intensity from ADC values. """
    df['Intensity'] = None

    for index, row in df.iterrows():
        try:
            pwm_value = int(row['PWM Value'], 16)
            intensity = (pwm_value / PWM_MAX) * 100
            df.at[index, 'PWM Value'] = pwm_value
            df.at[index, 'Intensity'] = intensity
            
        except ValueError:
            df.drop(index, inplace=True)

    return df


def main():
    """ Main function to execute the data acquisition process. """
    print("Initializing serial connection...")
    ser = initialize_serial_connection("COM4", 9600)
    print("Reading serial data...")
    raw_df = read_serial_data(ser, 15)
    ser.close()
    processed_df = process_data(raw_df)
    print(processed_df)
    save_data_to_csv(processed_df, 'outputData.csv')
    plot_data(processed_df)

if __name__ == "__main__":
    main()
