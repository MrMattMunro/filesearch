<%@ page contentType="text/html;charset=utf-8" language="java"%>
<html>
<head>
<meta http-equiv="content-type" content="text/html;charset=UTF-8" />
<meta http-equiv="Content-Style-Type" content="text/css" />
<script type="text/javascript" src="<%=request.getContextPath()%>/web/js/common.js"></script>
<script language="JavaScript" src="<%=request.getContextPath()%>/web/js/jquery.js"></script>
<script language="JavaScript" src="<%=request.getContextPath()%>/web/js/swfobject.js"></script>
<LINK href="<%=request.getContextPath()%>/web/css/default.css" rel="stylesheet" type="text/css">
<script type="text/javascript">
  var swffile; 
  <%
     String swffile=(String)session.getAttribute("swffile");
     swffile = "../" + swffile;
  %>
  var swffile = "<%=swffile%>";
  
  function loadswf(){
	 var so = new SWFObject(swffile,swffile, "800", "620", "7", "#ffffff");
     var dividex = "viewDiv";
     so.write(dividex);
  }
</script>
<title>Results</title>
</head>
<body onload="loadswf()">
<div id="viewDiv"></div>
</body>
</html>
