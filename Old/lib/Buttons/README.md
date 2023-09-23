-----------------------------------------------------------------------------------------------------------------------------
My Button Classes
-----------------------------------------------------------------------------------------------------------------------------

Button classes in c++ and the raylib library.

 Alejandro (Alex) Ricciardi  
 created date: 01/05/2023  
 Initialized with MyRaylibTemplate  
 https://github.com/Omegapy/MyRaylibTemplate  

-----------------------------------------------------------------------------------------------------------------------------
Requirements:  

c and c++ 20 or later    
MS Windows 10 or later   
Raylib library: https://www.raylib.com  

<p align="left">
  <img width="75" height="75" src="https://user-images.githubusercontent.com/121726699/215234958-2659b12a-4181-4f6b-a757-3e868244192e.png">
  <img width="200" height="100" src="https://user-images.githubusercontent.com/121726699/215234968-9f5961e4-8ca0-4f4e-acdc-53c1817547dd.png">
</p>

-----------------------------------------------------------------------------------------------------------------------------
Project description:

The project contains my button classes in c++ and the raylib library.

<p align="center">
 <img width="150" height="75"src="https://user-images.githubusercontent.com/121726699/215300372-34bd2249-3a93-49cf-a213-71ddeb2f0a62.png">
</p>

~~~c++
/*
    The ButtonR class creates a rectangle shaped static-size button, window-resized-not-responsive button.
      
    The button size is computed from the font size and length of the text; 
    the text is automatically centered on the button.
    See mutators to  modify the button’s position, the text’s position in the button, and the button’s size.

    The button's border can be turn on and off.
    the border's size is computed from the font size and length of the text;
    modifying the button's size will also modify the border's size.

    The button's shadow can be turn on and off.
    The shadow size is computed from the font size and length of the text;
    modifying the button's size will also modify the shadow's size.

    The default font is raylib font.
      
    Parent class to the ButtonO class
*/
ButtonR button;
~~~
~~~c++
/*
    The ButtonO class creates a rounded edges rectangle shaped static-size button, 
    window-resized-not-responsive button.

    The button size is computed from the font size and length of the text;
    the text is automatically centered on the button.
    See mutators to  modify the button’s position, the text’s position in the button, and the button’s size.

    The button's border can be turn on and off.
    the border's size is computed from the font size and length of the text;
    modifying the button's size will also modify the border's size.

    The button's shadow can be turn on and off.
    The shadow size is computed from the font size and length of the text;
    modifying the button's size will also modify the shadow's size.

    The default font is raylib font.
      
    Child class of ButtonR class
*/
ButtonO button;
~~~
~~~c++
/*
    The ButtonP class creates a responsive button from an image.
    (The button resizes with the window)

    The button size is computed from the font size and length of the text;
    the text is automatically centered on the button.
    See mutators to modify the button’s position, the text’s position in the button, and the button’s size.

    The default font is raylib font.
*/
ButtonP button;
~~~

Link: <a href='https://github.com/Omegapy/MyButtonClasses/wiki/Image-How-To-ButtonP-Class'>Image How To ButtonP Class</a>

-----------------------------------------------------------------------------------------------------------------------------
Credits:

Example button image:  
<a href='https://pngtree.com/so/icons'>icons png from pngtree.com</a>

-----------------------------------------------------------------------------------------------------------------------------

Links:  
Project GitHub: https://github.com/Omegapy/MyButtonClasses  
GitHub: https://github.com/Omegapy  
YouTube: https://www.youtube.com/watch?v=I_9yhN82opo&t=17   
Facebook: https://www.facebook.com/profile.php?id=100089638857137  
Twitter: https://twitter.com/RicciardiAlex

