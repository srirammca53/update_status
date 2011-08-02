var myImg= new Array(9)
  myImg[0]= "1.jpg";
  myImg[1]= "2.jpg";
  myImg[2]= "3.jpg";
  myImg[3]= "4.jpg";
  myImg[4]= "5.jpg";
  myImg[5]= "6.jpg";
  myImg[6]= "7.jpg";
  myImg[7]= "8.jpg";
  myImg[8]= "9.jpg";
  myImg[9]= "10.jpg";

var i = 0;

function slideshow(i)
{
document.img.src = myImg[i];
}

function slideshow2(i)
{
document.img.src = myImg[i];
}


function prev()
	{
        
	if(i<1)
	  {
	    var l = i
	  } 
	else 
	  {
	    var l = i-=1;
              
	  }
 document.img.src = myImg[l];
 document.f.las.disabled=false;
 document.f.nxt.disabled=false;
document.f.fir.disabled=false;
if(l==0)
{
document.f.pre.disabled=true;
document.f.fir.disabled=true;
document.f.nxt.disabled=false;
document.f.fir.disabled=true;
}

	}


function next()
     {

	if(i>9)
	      {
	      var l = i
	      } 

	else 
	     {
	     var l = i+=1;
	     }
	   document.img.src = myImg[l];
document.f.pre.disabled=false;
document.f.nxt.disabled=false;
document.f.las.disabled=false;
document.f.fir.disabled=false;
if(l==9)
{
document.f.nxt.disabled=true;
document.f.las.disabled=true;
document.f.fir.disabled=false;
}


 }

function start()
	{
        	var i=0;
	do{
	timer = setInterval("slideshow(i++)",1000);      	
	}while(i==10);
          }

	

function stop() 
	{
	clearInterval(timer);
	}

function first()
{
document.img.src = myImg[0];
document.f.fir.disabled=true;
document.f.nxt.disabled=false;
document.f.pre.disabled=true;
document.f.las.disabled=false;
}

function last()
{
document.img.src = myImg[9];
document.f.nxt.disabled=true;
document.f.pre.disabled=false;

}



