
<a name="readme-top"></a>



[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- PROJECT LOGO -->
<br />
<div align="center">
 

<h3 align="center">Framee</h3>

  <p align="center">
   A Highly Performant Image processor
    <br />
    <a href="https://github.com/parmyspn/Framee"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/parmyspn/Framee">View Demo</a>
    ·
    <a href="https://github.com/parmyspn/Framee/issues">Report Bug</a>
    ·
    <a href="https://github.com/parmyspn/Framee/issues">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project



Framee is a well tested image processor command line application. It consists of three major fields of image processing: image filtering,  noise reduction and compressor. Each of these is implemented by a different data structure to serve the purpose in the most efficient way. 

Framee filtering uses image convolution to achieve image bluring, sharpening, ridge and edge detection. One can adjust images' brightness, vibrance and warmth by -100% to 100%.

Framee denoising can reduce image noises caused by pixels with the minimum luminance or with the minimum total of hue difference with its surrounded pixels. It replaces these pixel by the average left and right pixels' hue. A doubly-linked list is used to achieve this funtionality.

Framee compressor uses a hierarchical structure, stores average color of a rectangular region at each node and it trims away portions of the tree representing areas without fine pixel-level detail. The portion is passed as tolerance parameter manually by the user. Other functionalities such as vertical and horizontal flips are added to this section because of the tree stucture used.



<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Built With

* c++

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

Clone the repository.
For Image filtering features of the app run 
```
cd Image-Filtering 
./framee 
```
then respopnd to your desire.
For compressor features run 
```
cd Image-Compressor 
./framee 
```
### Prerequisites

You need to have cpp installed.
Images should be in png format.



<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage
- [ ] **Image Filtering Demo**

* Blur 

![blurred-img][blurred-url]

* Sharpen

![sharpened-img][sharpened-url]

* Edge Detect

![EdgeDetect-Img][edgeDetect-url]

* Ridge Detect

![RidgeDetect-Img][ridgeDetect-url]

* Brightness 30% Vibrance 45% Warmth 20%

![Brightness-Vibrance-Warmth-Img][brightness-vibrance-warmth-url]

* Denoise a pepper and salt noised image

![Noised-Img][noised-url]


- [ ] **Image Compressor Demo**

* Original Image

![Compressor-Img][compressor-url]

* Pruned with 0.002 rate

![Prune-Tol002][prune-002-url]

* Prune with 0.005 rate

![Prune-Tol005][prune-005-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>





<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

Your Name - [@parmisparvin](www.linkedin.com/in/parmisparvin) - parmisprv@gmail.com

Project Link: [https://github.com/parmyspn/framee](https://github.com/parmyspn/framee)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

* This project uses cs221util -UBC's HSLAPixel library- 


<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/parmyspn/Framee.svg?style=for-the-badge
[contributors-url]: https://github.com/parmyspn/Framee/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/parmyspn/Framee.svg?style=for-the-badge
[forks-url]: https://github.com/parmyspn/Framee/network/members
[stars-shield]: https://img.shields.io/github/stars/parmyspn/Framee.svg?style=for-the-badge
[stars-url]: https://github.com/github_username/repo_name/stargazers
[issues-shield]: https://img.shields.io/github/issues/parmyspn/Framee.svg?style=for-the-badge
[issues-url]: https://github.com/parmyspn/Framee/issues
[license-shield]: https://img.shields.io/github/license/parmyspn/Framee.svg?style=for-the-badge
[license-url]: https://github.com/parmyspn/Framee/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/parmisparvin/
[blurred-url]: https://user-images.githubusercontent.com/93885987/195722957-6f21c17d-d34d-43e2-a9cc-6f578f3f6e47.jpg
[sharpened-url]: https://user-images.githubusercontent.com/93885987/195723220-70776362-4596-4f6a-bdc3-f1f38d92d604.jpg
[edgeDetect-url]: https://user-images.githubusercontent.com/93885987/195723341-c51b1178-e99e-44b6-9f69-e6bbe95c52e1.jpg
[ridgeDetect-url]: https://user-images.githubusercontent.com/93885987/195723543-bdd15852-56da-4c9f-bb6c-b0ad0f1774cf.jpg
[brightness-vibrance-warmth-url]: https://user-images.githubusercontent.com/93885987/195723668-c4311b5a-542b-4bf6-8f40-9bfa94b524f7.jpg
[noised-url]: https://user-images.githubusercontent.com/93885987/195723902-e08fb131-c27d-4c87-8970-90aed9a469e6.jpg
[compressor-url]: https://user-images.githubusercontent.com/93885987/195724597-77b032d6-d788-405a-99b2-dedeb0c70ac2.png
[prune-005-url]: https://user-images.githubusercontent.com/93885987/195724680-87153714-2dba-4c02-9e27-9ac4db1a71e9.png
[prune-002-url]: https://user-images.githubusercontent.com/93885987/195724729-bd12b11b-ab11-475b-aaa7-3c939522e0cb.png 

[product-screenshot]: https://user-images.githubusercontent.com/93885987/195710194-7129184f-3994-4b81-bc39-3d03ef1ddf9c.png
[Angular.io]: https://img.shields.io/badge/Angular-DD0031?style=for-the-badge&logo=angular&logoColor=white
[Angular-url]: https://angular.io/
[Svelte.dev]: https://img.shields.io/badge/Svelte-4A4A55?style=for-the-badge&logo=svelte&logoColor=FF3E00
[Svelte-url]: https://svelte.dev/
[Laravel.com]: https://img.shields.io/badge/Laravel-FF2D20?style=for-the-badge&logo=laravel&logoColor=white
[Laravel-url]: https://laravel.com
[Bootstrap.com]: https://img.shields.io/badge/Bootstrap-563D7C?style=for-the-badge&logo=bootstrap&logoColor=white
[Bootstrap-url]: https://getbootstrap.com
[JQuery.com]: https://img.shields.io/badge/jQuery-0769AD?style=for-the-badge&logo=jquery&logoColor=white
[JQuery-url]: https://jquery.com 
