# Fast Image Annotation Tool (FIAT)

## Abstract

FIAT is a simple cross platform tool build for image data annotation using rectangles. It is based on OpenCV high GUI. The User can select rectangular regions of interests whilst assigning class names to each object.

## Dependencies

- Boost Library: 1. program_options
                 2. filesystem
                 3. system
- OpenCV 3 Library: 1. imgproc
                    2. core
                    3. highgui
                    4. imgcodecs

Preferably if a Qt backed OpenCV is better for a neat UI - c.f. [Windows installation tutorial](http://docs.opencv.org/3.1.0/d3/d52/tutorial_windows_install.html#gsc.tab=0) on Windows platforms .

## Folder architecture

The folder hierarchy should resemble that of the PASCAL challenge: i.e.

```txt
data/
    |-- Annotations/
         |-- *.txt (Annotation files)
    |-- Images/
         |-- *.png (Image files)
    |-- ImageSets/
         |-- train.txt
```

For each image in `data/Images/foo.png`should correspond an annotation file `data/Annotations/foo.txt` containing objects' coordinates and their classes:

```csv
bar <x1> <x2> <y1> <y2>LF
```

## Building

Run CMake to generate the project on Linux, OS X and Windows and proceed to build.

On Linux/OS X:

```bash
cd /path/to/FIAT
mkdir build && cd build
cmake .. [-D options]
make all
```

Example: on OS X if building with the OpenCV installed by homebrew, cmake options might look like:

```bash
cmake -DCMAKE_PREFIX_PATH=/usr/local/opt/opencv3 ..
```

On Windows:

```cmd
cd /path/to/FIAT
mkdir build && cd build
```

Now open CMake GUI, generate a VS project and build the program.

## Tutorial

To launch the annotation program, run:

```bash
/path/to/annotate --images /path/to/data/Images/ --annotations /path/to/data/Annotations --min_dim <minimal dimension size>
```

To get help run:

```bash
/path/to/annotate --help
```

Controls:

-  **Mouse**: click with mouse to select upper-left and lower-right corners of a rectangle
-  **Confirm: 'c' key**: confirm selection
   -  After confirming switch to terminal window and enter a label for the selection; press enter
   -  After labeling switch back to image window and repeat for each annotation, using mouse to select a new rectangle.
-  **Delete: 'd' key**: delete previous annotation rectangle
-  **Next: 'n' ney**: move to next image
-  **ESC**: next image

const int Confirm = 99; // 'c' key
const int Next = 110;   // 'n' key
const int Delete = 100; // delete key
const int ESC = 27;     // escape key

It is strongly recommended that you run the program without specifying the annotations directory, as it would be inferred automatically.
Example:

```bash
./bin/annotate --images ~/Desktop/Database/data/Images --min_dim 224
```

## To do

- Complete documentation.
- Improve annotation interface.
- Create unit tests.
- Add a second window to help tracking annotations and enter classes without going back to terminal.
