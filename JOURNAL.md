---
title: "LED CUBE"
github: "https://github.com/rosan-24/led-cube"
description: "4x4x4 led cube powered by esp32"
created_at: "2026-11-06"
total_time: "10h 24m"
---
---
title: "LED CUBE"
github: "https://github.com/rosan-24/led-cube"
description: "4x4x4 led cube powered by esp32"
created_at: "2026-11-06"
total_time: "1h 42m"
---

# November 7, 2026: Zero to something; Learned the basics of Kicad
<!-- fabricate:entry 2363 -->

> So basically, From the scratch I gathered the list of components needed to build the LED Cube and started to sketch a schematic. KiCad is new to me, so I went through YouTube videos and found a channel. After some videos I was able to create few connections.
 
> One thing I faced was there is not symbol for ESP32-DevKit, so I was made to create my, own symbol for ESP32-DevKit, with so loophole I was able to create the symbol.

> I also created a 7Semi TPS61023 symbol not the exact one just a reference one. And I also added holes for the LEDs and resister 

> Footprints are added to some and yet to be added for someother symbols

> Seeyaa...!!

![](https://fabricate.hackclub-assets.com/d66da5e8dd76e01f9ee6a565f483cc11f8943e69c17cc801ba974b01db44e861/image-png/Screenshot%202026-11-07%20114104.png)
![](https://fabricate.hackclub-assets.com/d6498c602451508a66183e703390b93efdadb2748cdc9cb141f730f84f7cf7b9/image-png/Screenshot%202026-11-07%20143100.png)
![](https://fabricate.hackclub-assets.com/3f91cfdc05afefc00010a7846194a656f3c80d2ca4cf4619392fc9610fe1014e/image-png/Screenshot%202026-11-07%20185147.png)


---
title: "LED CUBE"
github: "https://github.com/rosan-24/led-cube"
description: "4x4x4 led cube powered by esp32"
created_at: "2026-11-06"
total_time: "4h"
---

**Total time spent: 1h 42m**

# November 11, 2026: Creation of new footprint...
<!-- fabricate:entry 2573 -->

> So basically, after two days today I sat and finished the footprint, and I also created a footprint for ESP, boost and charger.

> It really took me more than 2 hours to create it and now the footprint is ready so we can proceed with next step..

>And I also reworked in the schematic diagram...

> So the next process it to arrange the components in its place..

> let me catch you on the next progress

![](https://fabricate.hackclub-assets.com/7f8d796381b89244f8b67146cf24e314e18fd8ec1fa6893c2280937f48deadca/image-png/Screenshot%202026-11-11%20002201.png)
![](https://fabricate.hackclub-assets.com/6733f04a8f4bf41c3433d25140df6cf054f1cb09d8d89da22dc548f5ffa46329/image-png/Screenshot%202026-11-11%20000625.png)
![](https://fabricate.hackclub-assets.com/82f2296596b845c5699a89bb73a6175514d02dd178b28d3f213e9cf825a32803/image-png/Screenshot%202026-11-10%20201455.png)

**Total time spent: 2h 18m**

# November 13, 2026: Wire connection
<!-- fabricate:entry 2900 -->

> So basically, what I did was trying to find how connect the wire and later I found that I have made a mistake but can't find the actual problem.   

> So, what's the real problem is I tried to label the pins but I failed in it, so I need to rework on it once again 

> And I connected the wires with the correct track width for each and everyone 

> And I also added the connection in two different layers so that there will be no clash between them one top and the other on the back

![](https://fabricate.hackclub-assets.com/3de39703fbf1ba9bd2a0f4aee2abfedb4ac0e2896bea956c52ce6b16f069ec8a/image-png/Screenshot%202026-11-13%20204850.png)
![](https://fabricate.hackclub-assets.com/d85abc685d9b5d0b8e60d4bfc1fd85160a725d71236425909152b8b9fd1da183/image-png/Screenshot%202026-11-13%20204906.png)
![](https://fabricate.hackclub-assets.com/8aa2dbfde4c10158abd2c86fb44ceb52dad44f007d7edbec63c952ebcda03d55/image-png/Screenshot%202026-11-13%20205009.png)
![](https://fabricate.hackclub-assets.com/7f8d796381b89244f8b67146cf24e314e18fd8ec1fa6893c2280937f48deadca/image-png/Screenshot%202026-11-11%20002201.png)
![](https://fabricate.hackclub-assets.com/a03c7166becfe0d81be6b02ccaa93aac5663e1a458ef3f3c40b5cb7a36521f5e/image-png/Screenshot%202026-11-11%20192723.png)

**Total time spent: 1h 18m**

# November 16, 2026: Casing for component
<!-- fabricate:entry 3203 -->

So basically, what's the thing is I have created a folder for the led components it's a box which was designed in onshape. 
through the process I have learned to use kicad and cad to design something related.
the next process is to create the code to run the program.

![](https://fabricate.hackclub-assets.com/729ed755c7e61043d40474f97d6e6d02b87bb57367a4ce4e9bfbfa42e7217722/image-png/Screenshot%202026-11-16%20195619.png)
![](https://fabricate.hackclub-assets.com/023b41e10b68bb8a86429e818bc19b342bb8134c28231398f5b61a6ec63b326d/image-png/Screenshot%202026-11-16%20200524.png)

**Total time spent: 2h 18m**

# November 18, 2026: Routed the pcb and resolved some design reviews.
<!-- fabricate:entry 3377 -->

In this devlog, i have finally resolved all the design errors on both schematic and pcb designs.

Now, everything is looking great. Still, they are a lot to do.
Still, i have to work on CAD design and then refining the pcb, generating gerber files, etc...

![](https://fabricate.hackclub-assets.com/fa87073271d14f5708598186583f40af4d110946ab5b8346cd6a5df0f7744fad/image-png/image.png)
![](https://fabricate.hackclub-assets.com/5bb48e02b5d7b379831a49075908c38e3ecadad26042a015c13800f8d01efeaf/image-png/image.png)

**Total time spent: 1h 48m**

# November 22, 2026: Final adjustment
<!-- fabricate:entry 3687 -->

So basically, I worked on organizing the LED layers and testing the connections to ensure everything lights up correctly. also created a hole to connect the esp32 to modify. and also added some text to the board, now it is ready for review...!!

![](https://fabricate.hackclub-assets.com/b3250c0f99b73d192d620e7c956c0888eaa942d740d2f6d274d12d965f08b94e/image-png/Screenshot%202026-11-22%20130144.png)
![](https://fabricate.hackclub-assets.com/eeeef4c406c6184206d142bd2e2f69982924c59d749288d740a90420bcab4f87/image-png/Screenshot%202026-11-22%20130043.png)
![](https://fabricate.hackclub-assets.com/75104cc7b37fb380ba8689f06c8119bcd6005d4483af301a8231b036e7170bf7/image-png/Screenshot%202026-11-21%20221956.png)
![](https://fabricate.hackclub-assets.com/84264bb7e91d9d86c7d9df82b23946c3261579da3cc5dab0afbe7a44eb307532/image-jpeg/ad8a799b46.jpg)

**Total time spent: 1h**
