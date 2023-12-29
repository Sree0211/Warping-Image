# Image Warping onto Cylindrical Projection

This C++ program uses OpenCV to warp an input image onto a cylindrical projection. The `BendImage` class provides methods for projecting a 2D image onto a cylindrical surface, considering the distortion due to the cylindrical shape.

This problem involves warping a flat image to appear as if it is the projection coming from a cylinder. The process consists of an orthographic projection of the image onto the curved surface of the cylinder, followed by a perspective projection back onto the image plane. The key is to represent this process backwards, by checking for every pixel in the new image where it appeared in the old image and setting its color. This involves setting up cylinder parameters, projecting a ray from the camera through each point in the new image to find its x, y, and z coordinates on the cylinder, and then using an orthographic projection to move that ray back to the image plane. The two free parameters that can be chosen are the cylinder radius and focal length, and it is important to ensure that the cylinder touches the image at the edges.

## Requirements

- OpenCV

## Usage

1. Clone the repository:

    ```bash
    git clone https://github.com/Sree0211/Warping-Image.git
    ```

2. Compile the C++ program:


3. Run the executable:

    ```bash
    ./bendImage
    ```

4. The program will load an example image, warp it onto a cylindrical projection, and display the result.

## Sample Output

![Output Image](https://github.com/Sree0211/Warping-Image/blob/main/output/wolves2.jpg)


