# Transport Catalogue

Transport directory.
- Accepts JSON-formatted data as input and outputs an SVG file visualizing stops and routes.
- Finds the shortest route between stops.
- Serialization of the directory database via Google Protobuf is implemented for computational acceleration.
- JSON constructor implemented to detect incorrect method sequences at compile time.

---

## Building the Project Instructions (Visual Studio)

1. Install Google Protobuf. Download the protobuf-cpp archive from the [official repository](https://github.com/protocolbuffers/protobuf/releases) and unpack it on your computer.
2. Create `build-debug` and `build-release` directories for building two Protobuf configurations. Prior to this, create a `package` directory where the Protobuf package will be stored.
3. Build and install the project (example with Debug build) using the following commands:
   ```
   cmake path\protobuf-3.15.8\cmake -DCMAKE_SYSTEM_VERSION=10.0.17763.0 -DCMAKE_BUILD_TYPE=Debug \ -Dprotobuf_BUILD_TESTS=OFF 
   \ -DCMAKE_INSTALL_PREFIX=path\protobuf-3.15.8\package
   cmake --build .
   cmake --install . 
   ```
4. In the `package` directory, you will find `bin\protoc.exe`, which will be used to compile proto files, and in the `lib` directory, static libraries for working with Protobuf.
5. To compile the proto file, execute the following command:
   `<path to Protobuf package>\bin\proto --cpp_out . transport_catalogue.proto`
6. Build the project using CMake:
   ```
   cmake . -DCMAKE_PREFIX_PATH=/path/to/protobuf/package
   cmake --build .
   ```
7. If necessary, add `include` and `lib` directories to the project's additional dependencies - Additional Include Directories and Additional Dependencies.

---

## Running the Program

To create a transport directory database and serialize it to a file based on `base_requests`, run the program with the `make_base` parameter, specifying the input JSON file.
Example of running the program to populate the database:
`transport_catalogue.exe make_base <base.json>`

To use the obtained database and deserialize it to respond to `stat_requests`, run the program with the `process_requests` parameter, specifying the input JSON file containing database queries and the output file that will contain responses to the queries.
Example of running the program to execute database queries:
`transport_catalogue.exe process_requests <req.json >out.txt`

---

## Format of Input Data

Input data is provided to the program via stdin in the format of a JSON object, structured as follows at the top level:
```
{
  "base_requests": [ ... ],
  "render_settings": { ... },
  "routing_settings": { ... },
  "serialization_settings": { ... },
  "stat_requests": [ ... ]
}
```
This is a dictionary containing keys:
- `base_requests` — an array describing bus routes and stops.
- `stat_requests` — an array of queries to the transport directory.
- `render_settings` — a dictionary for image rendering.
- `routing_settings` — a dictionary containing settings for bus speed and waiting time at stops.
- `serialization_settings` — serialization settings.

---

### Populating the Transport Directory Database

#### Serialization of the Database
The `file` key specifies the filename from which to read the serialized database.
```
"serialization_settings": {
    "file": "transport_catalogue.db"
}
```

#### Example of Stop Description:
```
{
  "type": "Stop",
  "name": "Electric Networks",
  "latitude": 43.598701,
  "longitude": 39.730623,
  "road_distances": {
    "Dokuchaev Street": 3000,
    "Liza Chaikina Street": 4300
  }
} 
```
A stop description is a dictionary with keys:
- `type` — a string equal to "Stop", indicating that the object describes a stop.
- `name` — the name of the stop.
- `latitude` and `longitude` specify the coordinates of the stop's latitude and longitude.
- `road_distances` — a dictionary specifying the distance to neighboring stops. The key is the name of the stop, and the value is an integer in meters.

#### Example of Bus Route Description:
```
{
  "type": "Bus",
  "name": "14",
  "stops": [
    "Liza Chaikina Street",
    "Electric Networks",
    "Dokuchaev Street",
    "Liza Chaikina Street"
  ],
  "is_roundtrip": true
} 
```
A bus route description is a dictionary with keys:
- `type` — a string "Bus", indicating that the object describes a bus route.
- `name` — the route name.
- `stops` — an array of stop names through which the bus route passes. For a circular route, the name of the last stop duplicates the name of the first stop.
- `is_roundtrip` — a boolean value. Indicates whether the route is circular.

#### Structure of the `render_settings` dictionary:
```
{
  "width": 1200.0,
  "height": 1200.0,
  "padding": 50.0,
  "line_width": 14.0,
  "stop_radius": 5.0,
  "bus_label_font_size": 20,
  "bus_label_offset": [7.0, 15.0],
  "stop_label_font_size": 20,
  "stop_label_offset": [7.0, -3.0],
  "underlayer_color": [255, 255, 255, 0.85],
  "underlayer_width": 3.0,
  "color_palette": [
    "green",
    [255, 160, 0],
    "red"
  ]
} 
```
- `width` and `height` — keys setting the width and height in pixels. A floating-point number in the range from 0 to 100000.
- `padding` — the padding of the map edges from the borders of the SVG document. A floating-point number greater than or equal to 0 and less than `min(width, height)/2`.
- `line_width` — the thickness of the lines used to draw bus routes. A floating-point number in the range from 0 to 100000.
- `stop_radius` — the radius of circles indicating stops. A floating-point number in the range from 0 to 100000.
- `bus_label_font_size` — the font size of bus route names. An integer in the range from 0 to 100000.
- `bus_label_offset` — the offset of the bus route name label relative to the coordinates of the final stop on the map. An array of two elements of type double, setting the `dx` and `dy` values of the `text` SVG element. Elements of the array are numbers in the range from -100000 to 100000.
- `stop_label_font_size` — the font size of stop names displayed. An integer in the range from 0 to 100000.
- `stop_label_offset` — the offset of the stop name relative to its coordinates on the map. An array of two double elements, setting the `dx` and `dy` values of the `text` SVG element. Numbers range from -100000 to 100000.
- `underlayer_color` — the color of the underlay under stop and route names.
- `underlayer_width` — the thickness of the underlay under stop and route names. Sets the value of the `stroke-width` attribute of the `<text>` element. A floating-point number in the range from 0 to 100000.
- `color_palette` — color palette. A non-empty array.
Colors can be specified:
   - as a string, e.g., `"red"` or `"black"`;
   - as an array of three integers in the range `[0, 255]`. These determine the `r`, `g`, and `b` components of the color in `svg::Rgb` format. The color `[255, 16, 12]` should be output as `rgb(255, 16, 12)`;
   - as an array of four elements: three integers in the range `[0, 255]` and one floating-point number in the range `[0.0, 1.0]`. They set the components `red`, `green`, `blue`, and `opacity` of the color in `svg::Rgba` format. The color specified as `[255, 200, 23, 0.85]` should be output as `rgba(255, 200, 23, 0.85)`.

#### Structure of the `routing_settings` dictionary
```
"routing_settings": {
    "bus_wait_time": 6,
    "bus_velocity": 40
} 
```
- `bus_wait_time` — waiting time for a bus at a stop, in minutes. Assume that whenever a person arrives at a stop, they will wait exactly the specified number of minutes for any bus. The value is an integer from 1 to 1000.
- `bus_velocity` — bus speed, in km/h. Assume that the speed of any bus is constant and exactly equal to the specified number. Waiting time at stops, acceleration, and braking times are not taken into account. The value is a floating-point number from 1 to 1000.
This configuration sets the waiting time to 6 minutes and the bus speed to 40 kilometers per hour.

---

### Queries to the Transport Directory

#### Query for information about a bus
