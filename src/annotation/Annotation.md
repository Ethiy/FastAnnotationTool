#Annotation doc:

The `Annotation` class stores coordinates and the class of each object annotated on the image.

We actually store the upper left and bottom down coordinates of the rectangle that englobes the object. We infer the rectangle height and width
to be available for further use if needed. For the annotation to be complete we need also to specify the object class.

The actual version implements only vertically (or horizontally) oriented rectangles: no rotation is taken into consideration for the moment.