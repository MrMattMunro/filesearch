<%@ page contentType="text/html;charset=utf-8" language="java"%>
<%@ page import="com.searchlocal.bean.*"%>
<%@ page import="com.searchlocal.entity.*"%>
<%@ page import="com.searchlocal.param.CreateNewParam"%>
<%@ page import="com.searchlocal.util.StringUtil"%>
<%@ page import="java.util.*"%>
<%@ page import="com.searchlocal.constants.Constant"%>
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
  var index; 
  <%
     String loadingMsg=(String)session.getAttribute(Constant.web_info_loading);
  %>
  var loadingMsg = "<%=loadingMsg%>";
  <%
     String view=(String)session.getAttribute(Constant.web_view);
  %>
  var view = "<%=view%>";
   <%
     String webinnewwin=(String)session.getAttribute(Constant.web_innewwin);
  %>
  var innewwin = "<%=webinnewwin%>";
  
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
		    node.href="pagetype?searchtype="+type;
		    tit.appendChild(node);
		    tit.innerHTML=tit.innerHTML+"&nbsp;&nbsp;&nbsp;";
        }
  }
  
  
  function fitPage(){
       GetDoc(swffile).FitPage();
  }
  
  function openInNewWindow(){
        var servletUrl = "/slfile/viewSwf";
        $.post(servletUrl,
               {"swffile":swffile},
               function(result) {  
                    var temp=eval("("+result+")");
               	    swffile = temp.swffile;
                    window.open("/slfile/web/viewswf.jsp","",'height=600, width=800,left=100,top=100, toolbar=no, menubar=no, scrollbars=no,resizable=no,location=no, status=no');
               }
        );
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
<title>Results</title>
</head>
<body onload="showMenu()">
<div id="msgarea" style="backgroundColor:beige;height:20px;width:600px">
	     <%
	        List msglist = (List) request.getAttribute(Constant.web_msg_list);
	        if(null != msglist && msglist.size() > 0){
	          System.out.println("hehdhdhdh");
	          for(int i=0;i< msglist.size(); i++){
	              MessageBean msgBean = (MessageBean)msglist.get(i);
	              String msgcode = msgBean.getMsgcode();
	              String msgType = msgBean.getMsgtype();
	              if(msgType.equals(Constant.MsgCode.ERR)){
	                 %>
	                   <span style="color:red;font-size:10;"><%=msgBean.getMsgcontent()%></span>
	                 <% 
	              }
	          }
	    %>
	    <%
	        }
	    %>
</div>
	<table width="100%" height="54" align="center" cellpadding="0" cellspacing="0">
		<tr valign=middle>
			<td width="100%" valign="top" style="padding-left:8px;width:137px;"
				nowrap><a href="http://www.slfile.net/"><img
				src="<%=request.getContextPath()%>/web/img/title.png" border="0" width="137" height="46"
				alt="<%=(String)session.getAttribute(Constant.web_returnhome)%>"></a></td>
			<td>&nbsp;&nbsp;&nbsp;</td>
			<td width="100%" valign="top">
			<div class="Tit" id="tit">
			</div>
			<table cellspacing="0" cellpadding="0">
				<tr>
					<td valign="top" nowrap><input type=hidden name=ie value="gb2312">
			        <form id ="searchform" action="slfile" method="post">
			        	<%  String query = (String) session.getAttribute("query");
		                %>
					    <input style="height: 26px;font-size: 13pt" id="query" name="query" value="<%=query%>" size="44"/>
					  	<input style="height: 28px;font-size: 11pt" type="submit" value="<%=(String)session.getAttribute(Constant.web_button)%>"/>
					  	<input type="hidden" name="pageMethod" id="pageMethod"/>
					  	<input type="hidden" name="pageNo" id="pageNo"/>
                    </form>
				</tr>
			</table>
			</td>
			<td></td>
		</tr>
	</table>
	<table width="100%" border="0" align="center" cellpadding="0"
		cellspacing="0" class="bi">
		<tr>
			<td nowrap>&nbsp;&nbsp;&nbsp;<a href="load"
				style="color:#000000 "><%=(String)session.getAttribute(Constant.web_returnhome)%></a></td>
			<%  
			    PageEntity pageEntity = (PageEntity) session.getAttribute("pageEntity");
		        CreateNewParam entity = (CreateNewParam) session.getAttribute("element");
		        if(null!=entity){
	        	    String path = entity.getPath();
			%>
			<td align="center" nowrap><%=(String)session.getAttribute(Constant.web_at)%><b><%=path%></b><%=(String)session.getAttribute(Constant.web_findfile)%>&nbsp;&nbsp;<%=pageEntity.getTotalRows() %><%=(String)session.getAttribute(Constant.web_rows)%>&nbsp;&nbsp;&nbsp;&nbsp;</td>
		    <%
		        }
		    %>
		</tr>
	</table>
	<table>
		<%
		    List beanList = (List) session.getAttribute("beanList");
			if (null != beanList) {
				for (int i = 0; i < beanList.size(); i++) {
					BaseFileBean bobj = (BaseFileBean) beanList.get(i);
					Object obj = beanList.get(i);
					String attachstring = "";
					String the = (String)session.getAttribute(Constant.web_the);
					String row = (String)session.getAttribute(Constant.web_row);
					
					String webpage = (String)session.getAttribute(Constant.web_page);
					if(obj instanceof WordFileBean){
						WordFileBean bean = (WordFileBean)obj;
						attachstring= the + bean.getParagraphNo()+(String)session.getAttribute(Constant.web_photogragh);
					}
					if(obj instanceof ExcelFileBean){
						ExcelFileBean bean = (ExcelFileBean)obj;
						attachstring= (String)session.getAttribute(Constant.web_excel_the)+
						   bean.getSheetname()+(String)session.getAttribute(Constant.web_excel_page)+bean.getRownb()+row;
					}
					if(obj instanceof PptFileBean){
						PptFileBean bean = (PptFileBean)obj;
						attachstring= the+bean.getPage()+webpage;
					}
					if(obj instanceof PdfFileBean){
						PdfFileBean bean = (PdfFileBean)obj;
						attachstring= the+bean.getPage()+ webpage;
					}
					if(obj instanceof ChmFileBean){
						ChmFileBean bean = (ChmFileBean)obj;
						attachstring= the+bean.getCatalogname()+(String)session.getAttribute(Constant.web_chapter);
					}
					if(obj instanceof TxtFileBean){
						TxtFileBean bean = (TxtFileBean)obj;
						attachstring= the+bean.getRownb()+row;
					}
					%>
		<tr>
			<td width="7px"></td>
			<td><a href="open?path=<%=bobj.getPath()%>">【<%=bobj.getFilename()%>】<%=attachstring%></a>&nbsp;&nbsp;
			<a class="previewlink" onclick="preview('<%= StringUtil.convertPath(bobj.getPath())%>' , '<%= i%>', this);"><%=(String)session.getAttribute(Constant.web_preview)%></a>
			&nbsp;&nbsp;&nbsp;&nbsp;<a class="viewlink" onclick="openInNewWindow();"><%=(String)session.getAttribute(Constant.web_view)%></a></td>
		</tr>
		<tr>
           	<td width="7px"></td>
            <td id ="previewDiv<%=i%>"></td>
		</tr>
		<tr>
			<td width="7px"></td>
			<td><%=bobj.getContent()%></td>
		</tr>
		<tr>
			<td width="7px"></td>
			<td style="color: #008000"><%=bobj.getPath()%>&nbsp;&nbsp;&nbsp;<FONT color=#000000><%=bobj.getLastmodify()%></FONT></td>
		</tr>

		<tr height="12px">
			<td></td>
		</tr>
		<%}
			}
		%>
	</table>
	<table>
		<%  
		    int pagenum = pageEntity.getTotalPages();
		    int currentpage = pageEntity.getCurrentPage();
		    String cpageNo = (String) request.getAttribute("cpageNo");
		%>
			<tr>
			<td width="7px"></td>
		<%  if (null != pageEntity) {
			    if(currentpage != 1){
		%>	    	
			    	   <td width="4px"/><td><a href="page?pageMethod=previous&cpageNo=<%=cpageNo%>"><%=(String)session.getAttribute(Constant.web_previouspage)%></a></td>
		<%	    }
			    int startpage = 0;
			    int endpage = 0;
			    if( pagenum+1 - currentpage > 10){
			    	startpage = currentpage-5;
			    	if(startpage<1){
			    		startpage=1;
			    	}
			    	endpage = startpage+10;
			    }else{
			    	startpage = currentpage-5;
			    	if(startpage<1){
			    		startpage=1;
			    	}
			    	endpage = pagenum+1;
			    }
			    
				for (int i = startpage; i < endpage; i++) {
					if(currentpage == i){
		%>
			           <td width="4px"/><td><%=i%></td>
		           <% }else{
						%>
					   <td width="4px"/><td><a href="page?pageNo=<%=i%>">[<%=i%>]</a></td>
						<% 
		              }
				 }
		         if(pagenum != 0 && currentpage != pagenum){
		        	 %>
					   <td width="4px"/><td><a href="page?pageMethod=next&cpageNo=<%=cpageNo%>"><%=(String)session.getAttribute(Constant.web_nextpage)%></a></td>
					 <% 
				 }
			}
		%>
			</tr>
	</table>
</body>
</html>
