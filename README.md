# Fast Image Annotation Tool (FIAT)

## Abstract

FIAT is a simple cross platform tool build for image data annotation using rectangles. It is based on OpenCV high GUI. The User can select rectangular regions of interests whilst assigning class names to each object.

## Dependencies

- Boost Library: - program_options
                 - filesystem
- OpenCV Library: - imgproc
                  - core
                  - highgui
                  - imgcodecs

## Folder architecture

The folder hierarchy should resemble that of the PASCAL challenge: i.e.

```
data/
    |-- Annotations/
         |-- *.txt (Annotation files)
    |-- Images/
         |-- *.png (Image files)
    |-- ImageSets/
         |-- train.txt
```

For each image in `data/Images/foo.png`should correspond an annotation file `data/Annotations/foo.txt` containing objects' coordinates and their classes:

```
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
make install
```

On Windows:

```cmd
cd /path/to/FIAT

```

## Tutorial
