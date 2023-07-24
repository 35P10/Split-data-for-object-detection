# Split data for object detection tasks

## Input

The program takes as input a directory path containing the data, which includes the images and their annotation files. It also takes as input a train_percentage value in the range [0.0, 1.0], which represents the percentage of data to be assigned to the training set.

```
./splitDataForObjectDetection path/to/data_directory train_percentage
```

**Structure of path/to/data_directory:**
```
path/to/data_directory/
    image1.jpg
    image1.txt
    image2.jpg
    image2.txt
    image3.jpg
    image3.txt
    ...
```


##  Output 

**Structure:**
```
path/to/data_directory/
    train/
        images/
            image1.jpg
            image2.jpg
            ...
        labels/
            image1.txt
            image2.txt
            ...
    val/
        images/
            image3.jpg
            image4.jpg
            ...
        labels/
            image3.txt
            image4.txt
            ...
```