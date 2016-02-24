#USB webcam node
Acquires an image from the web cam, sizes and compresses it using openCV and then publishes it to imageJpg

The frame rate is 1Hz

To launch:
```
rosrun mars_webcam mars_webcam_node
```
or in a launch file 
```
<node name="webcam" pkg="mars_webcam" type="mars_webcam_node">
  <remap from="imageJpg" to="webcamImageJpg"/>
</node>
```
