function hiddle(){
  var menudiv = document.getElementById("gb");
  if(menudiv.style.visibility == 'visible'){
     menudiv.style.visibility = 'hidden';
  }
}
function show(){
      var menudiv = document.getElementById("gb");
      menudiv.style.visibility = 'visible';
}

function GetDoc(movieName) {
    var isIE = navigator.appName.indexOf("Microsoft") != -1;
    return (isIE) ? window[movieName] : document[movieName];
}


function getExplore(){
      if (window.navigator.userAgent.indexOf("MSIE")>=1){
			if (window.navigator.userAgent.indexOf("MSIE 6.0")>=1 )
			 {
			    return "ie6"  
			 }
			 if (window.navigator.userAgent.indexOf("MSIE 7.0")>=1 )
			 {
		        return "ie7"  
			 }
			 if (window.navigator.userAgent.indexOf("MSIE 8.0")>=1 )
			 {
		        return "ie8"  
			 }
			 if ( window.navigator.userAgent.indexOf("MSIE 9.0")>=1 )
			 {
		        return "ie9"  
			 }
	  }else{
	        if (window.navigator.userAgent.indexOf("Firefox")>=1){
               return "firefox"
            }  
	  }
}
	

function Search() {
	alert(swffile);
    GetDoc(swffile).SearchText(document.all.searchbox.value);
}

 var requiredMajorVersion = 8;
 var requiredMinorVersion = 0;
 var requiredRevision = 0;

 var isIE  = (navigator.appVersion.indexOf("MSIE") != -1) ? true : false;
 var isWin = (navigator.appVersion.toLowerCase().indexOf("win") != -1) ? true : false;
 
 function JSGetSwfVer(i){
             if (navigator.plugins != null && navigator.plugins.length > 0) {
                         if (navigator.plugins["Shockwave Flash 2.0"] || navigator.plugins["Shockwave Flash"]) {
                                    var swVer2 = navigator.plugins["Shockwave Flash 2.0"] ? " 2.0" : "";
                         var flashDescription = navigator.plugins["Shockwave Flash" + swVer2].description;
                                    descArray = flashDescription.split(" ");
                                    tempArrayMajor = descArray[2].split(".");
                                    versionMajor = tempArrayMajor[0];
                                    versionMinor = tempArrayMajor[1];
                                    if ( descArray[3] != "" ) {
                                                tempArrayMinor = descArray[3].split("r");
                                    } else {
                                                tempArrayMinor = descArray[4].split("r");
                                    }
                         versionRevision = tempArrayMinor[1] > 0 ? tempArrayMinor[1] : 0;
             flashVer = versionMajor + "." + versionMinor + "." + versionRevision;
             } else {
                                    flashVer = -1;
                         }
             }
             else if (navigator.userAgent.toLowerCase().indexOf("webtv/2.6") != -1) flashVer = 4;
             else if (navigator.userAgent.toLowerCase().indexOf("webtv/2.5") != -1) flashVer = 3;
             else if (navigator.userAgent.toLowerCase().indexOf("webtv") != -1) flashVer = 2;
             else {                       
                         flashVer = -1;
             }
             return flashVer;
 } 
 
 function DetectFlashVer(reqMajorVer, reqMinorVer, reqRevision) 
 {
             reqVer = parseFloat(reqMajorVer + "." + reqRevision);
             for (i=25;i>0;i--) {       
                         versionStr = JSGetSwfVer(i);              
                         if (versionStr == -1 ) { 
                                    return false;
                         } else if (versionStr != 0) {
                                    versionArray      = versionStr.split(".");
                                    
                                    versionMajor      = versionArray[0];
                                    versionMinor      = versionArray[1];
                                    versionRevision   = versionArray[2];
                                    
                                    versionString     = versionMajor + "." + versionRevision;   
                                    versionNum        = parseFloat(versionString);
                                    if ( (versionMajor > reqMajorVer) && (versionNum >= reqVer) ) {
                                                return true;
                                    } else {
                                                return ((versionNum >= reqVer && versionMinor >= reqMinorVer) ? true : false );    
                                    }
                         }
             }          
             return (reqVer ? false : 0.0);
 }
 function preview(filepath, index, obj){
 	    var el = obj.parentElement;
        el.children.item(2).style.visibility = "visible";
 	    var divid = "#previewDiv" + index;
 	    var loadMsg = "<p align='center'>" + loadingMsg + "</p>";
 	    $(divid).html(loadMsg);
 	    
        var servletUrl = "/slfile/previewDoc";
        $.post(servletUrl,
               {"filepath":filepath,"index":index},
               function(result) {  
               	    var temp=eval("("+result+")");
               	    swffile = temp.swffile;
				    index = temp.index;
					var so = new SWFObject(swffile,swffile, "500", "165", "7", "#ffffff");
					clearSwf();
		            var dividex = "previewDiv" + index;
                    so.write(dividex);
                    window.setTimeout("fitPage()", 1000);
               }
        );
}
function clearSwf(){
	for(var i = 0; i<8; i++){
	   var dividex = "previewDiv" + i;
	   var previewDiv = document.getElementById(dividex);
	   if(previewDiv != undefined){
	      previewDiv.innerHTML="";
	   }
	}
}
function formatMsg(current){
	var argCount = 0;
	var m = current.match(/\{\d+\}/g);
	if (!m) {
		return current;
	} else 	if (arguments.length < m.length + 1) {
		Logger.warn('Util.Message#get : arguments short [' + key + '] requires ' +
		m.length + ' arguments');
	} else {
		for (i = 0; i < m.length; i++) {
			current = current.replace(m[i], arguments[i + 1]);
		}
	}
	return current;
}

function replaceAll(content, s1, s2){
    while(content.indexOf(s1) != -1){
    	content = content.replace(s1,s2);
    }
    return content;
}
