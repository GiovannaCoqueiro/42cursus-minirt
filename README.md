<h1 align=center>
	<b>42cursus</b>
</h1>

<div align=center>
	<h2>
		<i>MiniRT</i>
	</h2>
	<img src="https://github.com/GiovannaCoqueiro/GiovannaCoqueiro/blob/main/badges/minirtm.png" alt=minirt_badge/>
	<p align=center>
    		Inside this repository, you can see all the code that has been created for the MiniRT project. The project was done in collaboration with <a href="https://github.com/ada-cruz">Aurora</a>
	</p>
</div>

---

<div align=center>
	<h2>
		Final score
	</h2>
	<img src="https://github.com/GiovannaCoqueiro/42cursus-minirt/assets/115947494/505cd54e-acdc-4f41-8897-be41d92e94df" alt=minirt_grade/>
</div>

---

<div align=left>
	<h3>
		Some images made with MiniRT
	</h3>
	<h4>
		composition.rt
	</h4>
	<img src="https://github.com/GiovannaCoqueiro/42cursus-minirt/assets/115947494/150f381f-33a2-4f34-8350-f1fd0547b7e0" alt=composition_image/>
	<h4>
		jamis.rt
	</h4>
	<img src="https://github.com/GiovannaCoqueiro/42cursus-minirt/assets/115947494/a611604b-b9c5-4ae0-bffd-8b80010cd2ad" alt=jamis_image/>
 	<h4>
		cylinders.rt
	</h4>
	<img src="https://github.com/GiovannaCoqueiro/42cursus-minirt/assets/115947494/a9376e43-832d-4cd5-8618-b6faf80c926b" alt=cylinders_image/>
</div>

---

<h4 align=left>
  Preparation
</h4>
<ul>
  <li>Use MinilibX.</li>
  <li>Turn in a Makefile to compile your program and it must not relink.</li>
  <li>The program must take as parameter a scene file ending with the '.rt' extension.</li>
</ul>

<h4 align=left>
  Scene
</h4>
<ul>
  <li>Implement at least three simple geometric objects: plane, sphere and cylinder.</li>
  <li>If applicable, all possible intersections and the inside of the object must be handled
correctly.</li>
  <li>Light management: spot brightness, hard shadows, ambiance lighting (objects are
never completely in the dark). You must implement Ambient and diffuse lighting.</li>
  <li>Your program must be able to apply translation and rotation transformation to
objects, lights and cameras (except for spheres and lights that cannot be rotated).</li>
  <li>Your program must be able to resize the object’s unique properties: diameter for a
sphere and the width and height for a cylinder.</li>
  <li>The scene must be a 3D view.</li>
</ul>

<h4 align=left>
  Graphic management
</h4>
<ul>
  <li>The program must display the image in a window.</li>
  <li>The window must close and the program must quit when the user press ESC or click on the cross on the window.</li>
	<li>The management of your window must remain fluid: switching to another window,
minimization, etc..</li>
</ul>

<h4 align=left>
  Scene
</h4>
<ul>
  <li>The scene file must be composed for three mandatory elements plus any object you want to render.</li>

  | Symbol | Element | Status |
  | :---: | :---: | :---: |
  | C | camera | mandatory |
  | A | ambient light | mandatory |
  | L | light | mandatory |
  | sp | sphere | optional |
  | pl | plane | optional |
  | cy | cylinder | optional |

  <li>Each element must follow some specific information separeted by white spaces.</li>
  <li>Camera:
	<ul>
		<li>Symbol: C</li>
	  	<li>x,y,z coordinates</li>
	  	<li>3D normalized orientation vector. Range [-1,1]</li>
	  	<li>FOV: horizontal field of view in degrees. Range [0,180]</li>
	</ul>
  </li>
  <li>Ambient Light:
	<ul>
		<li>Symbol: A</li>
	  	<li>Ratio. Range [0.0,1.0]</li>
		<li>R,G,B color. Range [0,255]</li>
	</ul>
  </li>
  <li>Light:
	<ul>
		<li>Symbol: L</li>
		<li>x,y,z coordinates</li>
	  	<li>Brightness ratio. Range [0.0,1.0]</li>
		<li>R,G,B color. Range [0,255] (it's mandatory to insert this info, but as we didn't implement the bonus part, the light used to create the scene will always be white)</li>
	</ul>
  </li>
  <li>Sphere:
	<ul>
		<li>Symbol: sp</li>
		<li>x,y,z coordinates</li>
	  	<li>Diameter</li>
		<li>R,G,B color. Range [0,255]</li>
	</ul>
  </li>
  <li>Plane:
	<ul>
		<li>Symbol: pl</li>
		<li>x,y,z coordinates</li>
	  	<li>3D normalized orientation vector. Range [-1,1]</li>
		<li>R,G,B color. Range [0,255]</li>
	</ul>
  </li>
  <li>Cylinder:
	<ul>
		<li>Symbol: cy</li>
		<li>x,y,z coordinates</li>
	  	<li>3D normalized orientation vector. Range [-1,1]</li>
		<li>Diameter</li>
		<li>Height</li>
		<li>R,G,B color. Range [0,255]</li>
	</ul>
  </li>
</ul>

<p>
	Exemple:
</p>
<img src="https://github.com/GiovannaCoqueiro/42cursus-minirt/assets/115947494/138f147a-27c1-4d44-b6e4-e5d2b2a31d8c" alt=scene_file_exemple/>

---

<h2>
    Instructions to use
</h2>
Clone this repository in you local computer using a terminal:

```sh
$> git clone git@github.com:GiovannaCoqueiro/42cursus-minirt.git [repository_local]
```
		
After cloning the project in your local reposiory you can run some commands you can find in Makefile:
<ul>
	<li>$> <b>make all:</b> or just <b>make</b> compiles the project</li>
	<li>$> <b>make val:</b> run the program with compilation.rt, using valgrind to search for leaks, you can change the .rt file by changing it in Makefile (I also recommend to decrease the size of the image in minirt.h to make this process faster, valgrind can take a lot of time)</li> 
	<li>$> <b>make clean:</b> deletes the object files created during compilation</li>
	<li>$> <b>make fclean:</b> executes the <b>clean</b> command and also deletes the binary created</li>
	<li>$> <b>make re:</b> executes the <b>fclean</b> command followed by the <b>all</b> command</li>
</ul>

Than you can run the program with:
```sh
./miniRT scenes/<image_file.rt>
```

You can also create and run any image, if it follows the requirements.
