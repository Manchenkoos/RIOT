import math

from PIL import Image, ImageDraw

# axis_color = (0xFF, 0xFF, 0xFF)
axis_color = (186, 199, 222)
measurement_color = (240, 250, 80)

def display_oscilloscope(draw):
    print("[Display] Oscilloscope")

    # x1 y1 x2 y2
    # Draw vertical lines
    for i in range(20, 320, 20):
        draw.line((i, 20, i, 220), fill=axis_color, width=1)

    # Draw horizontal lines
    for i in range(20, 240, 20):
        draw.line((20, i, 300, i), fill=axis_color, width=1)

    # Draw axis
    # Vertikal
    for i in range(20, 220, 4):
        draw.line((159, i, 161, i), fill=axis_color, width=1)
    
    # Horizontal
    for i in range(20, 300, 4):
        draw.line((i, 119, i, 121), fill=axis_color, width=1)

    return draw

def display_measurements(draw, measurements):
    print("[Display] Measurements")

    # x1 y1 x2 y2

    # last_measurement
    for i in range(280):
        print(int((measurements[i]   * (5 * 20)) + 120))
        if (i == 279):
            break
            # last_measurement
        # measurement = int((measurements[i] * (5 * 20)) + 120)

        # print(measurement)

        measurement_start = int((measurements[i]   * (5 * 20)) + 120)
        measurement_end   = int((measurements[i+1] * (5 * 20)) + 120)

        # draw.line((i+20, measurement, i+20, measurement), fill=(0xFF, 0xFF, 0xFF), width=1)
        # draw.line((i+21, measurement_start, i+21, measurement_end), fill=measurement_color, width=1)
        if (measurement_start > measurement_end):
            draw.line((i+21, measurement_start, i + 21, measurement_end + 1), fill=measurement_color, width=1)
        else:
            draw.line((i+21, measurement_start, i + 21, measurement_end - 1), fill=measurement_color, width=1)

    return draw

if __name__ == "__main__":
    print("[Display] Start")

    im   = Image.new('RGB', (320, 240), (0x00, 0x00, 0x00)) 
    draw = ImageDraw.Draw(im) 

    measurements = []

    # 280
    for i in range(280):
        measurements.append(math.sin(i/18))

    draw = display_oscilloscope(draw)
    draw = display_measurements(draw, measurements)

    # 300*220

    im.show()
    # im.save('1.png', 'PNG')