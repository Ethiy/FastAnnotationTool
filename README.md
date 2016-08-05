# Fast Image Annotation Tool (FIAT)

## Abstract:

FIAT is a simple tool build for image data annotation using rectangles. It is based on OpenCV high GUI. The User can select rectangular regions of interests whilst assigning class names to each object.

## Dependencies:

- Boost Library: - program_options
                 - filesystem
- OpenCV Library: - imgproc
                  - core
                  - highgui
                  - imgcodecs

## Folder architecture:

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

You can build the project on Unix/Mac systems using the Makefile. You should however make sure Boost and OpenCV directories  in lines #15 to #20 are the right ones. 

On Windows, you can use Cmake to generate the project - on Visual Studio for instance - and build it.

## Tutorial

