<%@ page contentType="text/html;charset=utf-8" language="java"%>
<%@ page import="java.util.*"%>
<%@ page import="com.searchlocal.param.CreateNewParam"%>
<%@ page import="com.searchlocal.util.StringUtil"%>
<%@ page import="com.searchlocal.constants.Constant"%>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<meta http-equiv="Content-Script-Type" content="text/javascript" />
<meta http-equiv="Content-Style-Type" content="text/css" />
<LINK href="<%=request.getContextPath()%>/web/css/default.css" rel="stylesheet" type="text/css">
<script type="text/javascript">
	function hiddle(){
	  var menudiv = document.getElementById("gb");
	  if(menudiv.style.visibility == 'visible'){
	     menudiv.style.visibility = 'hidden';
	  }
	}
	var screenwidth = screen.width;
	function adjustTit(){
	  var titDiv = document.getElementById("tit");

	  if(screenwidth != 1024 && screenwidth != 800){
	     titDiv.style.width="32%";
	  }
	  
	  if(screenwidth == 800){
	      titDiv.style.width="52%";
	  }

	  if(screenwidth == 1024){
	      titDiv.style.width="41%";
	  }
	
	}

	function show(){
	      var menudiv = document.getElementById("gb");
	      menudiv.style.visibility = 'visible';
	      menudiv.style.position="absolute";
	      if (window.navigator.userAgent.indexOf("MSIE")>=1){
				if (window.navigator.userAgent.indexOf("MSIE 6.0")>=1)
				 {
				   menudiv.style.top=28; 
                   menudiv.style.left=151; 
				 }
				 if (window.navigator.userAgent.indexOf("MSIE 7.0")>=1  ||  window.navigator.userAgent.indexOf("MSIE 8.0")>=1 || 
					 window.navigator.userAgent.indexOf("MSIE 9.0")>=1)
				 {
			       menudiv.style.top=30; 
                   menudiv.style.left=170;  
				 }
		  }else{
		        if (window.navigator.userAgent.indexOf("Firefox")>=1){
		       
	               menudiv.style.top=28; 
                   menudiv.style.left=200;
                }  
		  }
	}
	
    function adapterPadding(){
	     var inputarea = document.getElementById("inputarea");
	 	 if (window.navigator.userAgent.indexOf("MSIE")>=1){
				if (window.navigator.userAgent.indexOf("MSIE 6.0")>=1)
				 {
				   inputarea.style.marginTop=28; 
				   inputarea.style.marginLeft=20;
				 }
				 if (window.navigator.userAgent.indexOf("MSIE 7.0")>=1)
				 {
			       inputarea.style.marginTop=9; 
				   inputarea.style.marginLeft=15;
				 }
		  }else{
		        if (window.navigator.userAgent.indexOf("Firefox")>=1){
                   inputarea.style.marginTop=30; 
				   inputarea.style.marginLeft=18;
                }  
		  }
	}
	function loadData(){
	      
        <%
        CreateNewParam obj = (CreateNewParam) session.getAttribute("element");
        if(null == obj){
        %>
		    window.document.forms[0].action="load";
	        window.document.forms[0].submit();
	    <%}%>
	    showMenu();
	    adapterPadding();
		adjustTit();
    }
    
    function buttonclick(){
        <%
	        if(null != obj){
	            request.setAttribute("searchname",obj.getSearchname());
	        }
        %>
    }
    
        
    function createtypenode(tit,innerHtml,type){
    <%
       String searchtype=(String)session.getAttribute("searchtype");
    %>
          if("<%=searchtype%>"==type){
	          var b = document.createElement('b');
		      b.innerHTML = innerHtml;
		      tit.appendChild(b);
		      tit.innerHTML=tit.innerHTML+"&nbsp;&nbsp;&nbsp;";
          }else{
              var node = document.createElement('a');
		      node.innerHTML = innerHtml;
		      node.href="type?searchtype="+type;
		      tit.appendChild(node);
		      tit.innerHTML=tit.innerHTML+"&nbsp;&nbsp;&nbsp;";
          }
    }
        
    function showMenu(){
       var tit = document.getElementById("tit");

       <%
        CreateNewParam param = (CreateNewParam) session.getAttribute("element");
        if(null != param){
        	List typeList = param.getSelectfiletype();
			if (null != typeList) {
	            %> 
				   createtypenode(tit,"<%=(String)session.getAttribute(Constant.web_allsearchtype)%>","all");
                <%
				for (int i = 0; i < typeList.size(); i++) {
	                String type = (String)typeList.get(i);
	                if(type.equals("excel")){
	                %> 
				      createtypenode(tit,"Excel","excel");
	        		<%
	                }
	                %>
	                <%
	                if(type.equals("word")){
	                %> 
	                  createtypenode(tit,"Word","word");
	        		<%
	                }
	                %>
	                <%
	                if(type.equals("pdf")){
	                %> 
	                  createtypenode(tit,"Pdf","pdf");
	        		<%
	                }
	                %>
	                <%
	                if(type.equals("ppt")){
	                %> 
	                  createtypenode(tit,"Ppt","ppt");
	        		<%
	                }
	                %>
	                <%
	                if(type.equals("html")){
		            %>
		              createtypenode(tit,"<%=(String)session.getAttribute(Constant.web_webpage)%>","html");
	        		<%
	                }
	                %>
	                <%
	                if(type.equals("txt")){
	                %> 
	                  createtypenode(tit,"<%=(String)session.getAttribute(Constant.web_source)%>","txt");
	        		<%
	                }
	                %>
	                <%
				}
		    }
        }
       %>
    }
</script>
<title>Local File Search</title>
<style></style>
</head>
<body onload="loadData()">
<div id=gbar style="margin-top: 0px;height: 20px;border:1px solid;border-right-color:#ffffff;border-top-color:#ffffff;border-left-color:#ffffff;border-bottom-color:#c9d7f1">
   <%
        Boolean isnosearch = (Boolean)session.getAttribute(Constant.is_no_search);
        List entityList = (List) session.getAttribute("entityList");
        CreateNewParam entity = (CreateNewParam) session.getAttribute("element");
        if(null!=entity && entityList.size() > 0){
        	String searchname = entity.getSearchname();
        	String path = entity.getPath();
        	String snamespace = StringUtil.makespace(searchname,10);
        	String pathspace = StringUtil.makespace(path,25);
   %>
        	<td class=gb3><%=(String)session.getAttribute(Constant.web_searchname)%></td><td><b><%=searchname%> <%=snamespace%></b></td>
            <td class=gb3><%=(String)session.getAttribute(Constant.web_searchpath)%> </td><td><b><%=path%><%=pathspace%></b></td>
    <%
        }else{
        %>
        	<td><%=(String)session.getAttribute(Constant.web_error_nosearcher)%></td>
        <%
        }
    %>
<a onclick="show()" onblur="hiddle()" class=gb3><u style=height:22px;vertical-align:top><%=(String)session.getAttribute(Constant.web_changesearch)%></u><small>&#9660;</small></a>
</div>
<br>

<table cellpadding=0 cellspacing=20 style="width: 100%">
	<tr valign=top align="center">
		<td><img src="<%=request.getContextPath()%>/web/img/title.png" style="width:150px;height:80px"></td>
	</tr>
</table>
<div id="inputarea" style="height:40px;" >
	<table cellpadding=0 cellspacing=0 style="width: 100%;">
		<tr>
			<td nowrap align="center">
			<div class="Tit" id="tit" style="height:20px;text-align:left;" >
			</div>	
			</td>
		</tr>
		<tr></tr>
		<tr>
			<td valign="top" nowrap align="center">
				<form id="searchform" action="slfile" method="post">
					&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input style="height: 26px;font-size: 13pt" name="query" size="44" id="query"/> 
					<input style="height: 28px;font-size: 11pt" type="submit" value="<%=(String)session.getAttribute(Constant.web_button)%>" />
					<%
					if(null!=obj){
					%>
					<input type="hidden" name="searchname" value="<%=obj.getSearchname()%>"/>
					<%
					}
					%>
				</form>
			</td>
		</tr>
	</table>
</div>
<div style="visibility: hidden; width:100px;border:1px solid;margin-left: 200px;border-color:#c9d7f1" id="gb"> 
<%
if(null!=entityList){
   for (Iterator iter = entityList.iterator(); iter.hasNext();) {
		CreateNewParam element = (CreateNewParam) iter.next();
		String searchname = element.getSearchname();
		%>
		<a href="change?searchname=<%=searchname%>" onclick="hiddle()" style="font-size: 10pt" class="gb2">&nbsp;<%=searchname%></a> 
		<%
	}
}
%>
</div>
</body>
</html>
