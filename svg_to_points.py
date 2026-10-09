from svgpathtools import svg2paths
import random
import os

NUM_POINTS = 2000

# can be swapped out for any other SVG file, header file, and variable name
FILES = [
    ("bearcat.svg", "BearcatPoints.h", "bearcatPoints"),
    ("dragon.svg", "DragonPoints.h", "dragonPoints"),
    ("pegasus.svg", "PegasusPoints.h", "pegasusPoints"),
    ("lion.svg", "LionPoints.h", "lionPoints"),
]

def sample_svg_points(svg_file, num_points):
    # extract all SVG path objects from the file
    paths, attrs = svg2paths(svg_file)

    all_points = []

    if len(paths) == 0:
        raise Exception(f"No paths found in {svg_file}")

    # distribute samples roughly evenly across all paths
    points_per_path = max(1, num_points // len(paths))

    for path in paths:

        for i in range(points_per_path):

            t = i / max(1, points_per_path - 1)

            p = path.point(t)

            all_points.append(
                [p.real, p.imag]
            )

    xs = [p[0] for p in all_points]
    ys = [p[1] for p in all_points]

    min_x = min(xs)
    max_x = max(xs)

    min_y = min(ys)
    max_y = max(ys)

    width = max_x - min_x
    height = max_y - min_y

    # scale shape to fit within 220x120 while maintaining aspect ratio, and center it in a 240x135 area
    scale_x = 220 / width
    scale_y = 120 / height

    scale = min(scale_x, scale_y)

    normalized = []

    for x, y in all_points:

        nx = (x - min_x) * scale
        ny = (y - min_y) * scale

        nx += (240 - width * scale) / 2
        ny += (135 - height * scale) / 2

        normalized.append(
            (int(nx), int(ny))
        )
    # Randomize point order so points appear across entire shape 
    # instead of drawn sequentially around the outline
    random.shuffle(normalized)

    if len(normalized) > num_points:
        normalized = normalized[:num_points]

    return normalized

def write_header(filename, variable_name, points):

    guard = filename.replace(".", "_").upper()

    with open(filename, "w") as f:

        f.write(f"#ifndef {guard}\n")
        f.write(f"#define {guard}\n\n")

        f.write(
            "struct Point {\n"
            "    uint16_t x;\n"
            "    uint16_t y;\n"
            "};\n\n"
        )

        f.write(
            f"const Point {variable_name}[{len(points)}] = {{\n"
        )

        for x, y in points:
            f.write(
                f"    {{{x}, {y}}},\n"
            )

        f.write("};\n\n")
        f.write("#endif\n")

# generate one header file for each SVG file, header_file, and variable_name in FILES
for svg_file, header_file, variable_name in FILES:

    print("Processing", svg_file)

    points = sample_svg_points(
        svg_file,
        NUM_POINTS
    )

    write_header(
        header_file,
        variable_name,
        points
    )

print("Done.")
