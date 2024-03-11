import math

def get_distance(start, end):
    x1, x2 = start[0], end[0]
    y1, y2 = start[1], end[1]

    X = (x1 - x2) ** 2 
    Y = (y1 - y2) ** 2

    return round((X+Y) ** (1/2), 2)

# def get_angle(p1, p2, p3):
#     v1 = x2 - x1
#     v2 = y2 - y1
#     # Calculate the angle in radians
#     angle_radians = math.atan2(dy, dx)

#     # Convert radians to degrees
#     angle_degrees = math.degrees(angle_radians)

#     # Ensure the angle is between 0 and 360 degrees
#     angle_degrees = (angle_degrees + 360) % 360

#     return angle_degrees