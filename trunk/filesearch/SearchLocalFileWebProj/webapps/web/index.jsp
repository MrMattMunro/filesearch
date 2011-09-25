<%@ page contentType="text/html;charset=utf-8" language="java"%>
<%@ page import="java.util.*"%>
<%@ page import="com.web.searchlocal.param.CreateNewParam"%>
<%@ page import="com.web.searchlocal.util.StringUtil"%>
<%@ page import="com.web.searchlocal.constants.Constant"%>
<html>
<head>
<link rel="stylesheet" href="<%=request.getContextPath()%>/web/css/jquery.ui.all.css">
<link rel="stylesheet" href="<%=request.getContextPath()%>/web/css/demos.css">

<script type="text/javascript" src="<%=request.getContextPath()%>/web/js/common.js"></script>
<script type="text/javascript" src="<%=request.getContextPath()%>/web/js/jquery/jquery-1.6.2.js"></script>
<script type="text/javascript" src="<%=request.getContextPath()%>/web/js/jquery/ui/jquery.ui.core.js"></script>
<script type="text/javascript" src="<%=request.getContextPath()%>/web/js/jquery/ui/jquery.ui.widget.js"></script>
<script type="text/javascript" src="<%=request.getContextPath()%>/web/js/jquery/ui/jquery.ui.tabs.js"></script>

<script type="text/javascript">

	$(function() {
		$( "#tabs" ).tabs({
			event: "mouseover"
		});
	});


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
		  if(screenwidth == 1920){
		      titDiv.style.width="21%";
		      titDiv.style.align="center";
		  }
	}

	function show(){
	      var menudiv = document.getElementById("gb");
	      menudiv.style.visibility = 'visible';
	      menudiv.style.position="absolute";
	      var explore = getExplore();
	      if (explore="ie6"){
      		   menudiv.style.top=28; 
               menudiv.style.left=60; 
	      } 
	      if (explore="firefox"){
               menudiv.style.top=28; 
               menudiv.style.left=30;
	      } 
	      if (explore="ie7"){
     	      menudiv.style.top=30; 
              menudiv.style.left=50;  
	      } 
	      if (explore="ie8"){
     	      menudiv.style.top=30; 
              menudiv.style.left=50;  
	      } 
	}
	
    function adapterPadding(){
	     var inputarea = document.getElementById("inputarea");
	     var explore = getExplore();
	     if (explore="ie6"){
			   inputarea.style.marginTop=28; 
			   inputarea.style.marginLeft=20;
	      }
	     if (explore="ie7"){
			   inputarea.style.marginTop=9; 
			   inputarea.style.marginLeft=15;
	      } 
	     if (explore="ie8"){
			   inputarea.style.marginTop=9; 
			   inputarea.style.marginLeft=15;
	      } 
	      if (explore="firefox"){
              inputarea.style.marginTop=30; 
			  inputarea.style.marginLeft=18;
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
	            request.setAttribute("id",obj.getId());
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

<div class="demo">
	<div id="tabs">
		<ul>
			<li><a href="#tabs-1">Nunc tincidunt</a></li>
			<li><a href="#tabs-2">Proin dolor</a></li>
			<li><a href="#tabs-3">Aenean lacinia</a></li>
		</ul>
		<div id="tabs-1">
			<p>Proin elit arcu, rutrum commodo, vehicula tempus, commodo a, risus. Curabitur nec arcu. Donec sollicitudin mi sit amet mauris. Nam elementum quam ullamcorper ante. Etiam aliquet massa et lorem. Mauris dapibus lacus auctor risus. Aenean tempor ullamcorper leo. Vivamus sed magna quis ligula eleifend adipiscing. Duis orci. Aliquam sodales tortor vitae ipsum. Aliquam nulla. Duis aliquam molestie erat. Ut et mauris vel pede varius sollicitudin. Sed ut dolor nec orci tincidunt interdum. Phasellus ipsum. Nunc tristique tempus lectus.</p>
		</div>
		<div id="tabs-2">
			<p>Morbi tincidunt, dui sit amet facilisis feugiat, odio metus gravida ante, ut pharetra massa metus id nunc. Duis scelerisque molestie turpis. Sed fringilla, massa eget luctus malesuada, metus eros molestie lectus, ut tempus eros massa ut dolor. Aenean aliquet fringilla sem. Suspendisse sed ligula in ligula suscipit aliquam. Praesent in eros vestibulum mi adipiscing adipiscing. Morbi facilisis. Curabitur ornare consequat nunc. Aenean vel metus. Ut posuere viverra nulla. Aliquam erat volutpat. Pellentesque convallis. Maecenas feugiat, tellus pellentesque pretium posuere, felis lorem euismod felis, eu ornare leo nisi vel felis. Mauris consectetur tortor et purus.</p>
		</div>
		<div id="tabs-3">
			<p>Mauris eleifend est et turpis. Duis id erat. Suspendisse potenti. Aliquam vulputate, pede vel vehicula accumsan, mi neque rutrum erat, eu congue orci lorem eget lorem. Vestibulum non ante. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Fusce sodales. Quisque eu urna vel enim commodo pellentesque. Praesent eu risus hendrerit ligula tempus pretium. Curabitur lorem enim, pretium nec, feugiat nec, luctus a, lacus.</p>
			<p>Duis cursus. Maecenas ligula eros, blandit nec, pharetra at, semper at, magna. Nullam ac lacus. Nulla facilisi. Praesent viverra justo vitae neque. Praesent blandit adipiscing velit. Suspendisse potenti. Donec mattis, pede vel pharetra blandit, magna ligula faucibus eros, id euismod lacus dolor eget odio. Nam scelerisque. Donec non libero sed nulla mattis commodo. Ut sagittis. Donec nisi lectus, feugiat porttitor, tempor ac, tempor vitae, pede. Aenean vehicula velit eu tellus interdum rutrum. Maecenas commodo. Pellentesque nec elit. Fusce in lacus. Vivamus a libero vitae lectus hendrerit hendrerit.</p>
		</div>
	</div>
</div>



<div id=gbar style="margin-top: 0px;height: 20px;border:1px solid;border-right-color:#ffffff;border-top-color:#ffffff;border-left-color:#ffffff;border-bottom-color:#c9d7f1">
   <%
        Boolean isnosearch = (Boolean)session.getAttribute(Constant.is_no_search);
        List entityList = (List) session.getAttribute("entityList");
        CreateNewParam entity = (CreateNewParam) session.getAttribute("element");
        if(null!=entity && entityList.size() > 0){
        	String path = entity.getPath();
        	String pathspace = StringUtil.makespace(path,25);
   %>
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
			    <div class="Tit" id="tit" style="height:20px;text-align:left;" ></div>	
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
					<input type="hidden" name="id" value="<%=obj.getId()%>"/>
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
		String id = element.getId();
		String path = element.getPath();
		%>
		<a href="change?id=<%=id%>" onclick="hiddle()" style="font-size: 10pt" class="gb2">&nbsp;<%=path%></a> 
		<%
	}
}
%>
</div>
</body>
</html>
