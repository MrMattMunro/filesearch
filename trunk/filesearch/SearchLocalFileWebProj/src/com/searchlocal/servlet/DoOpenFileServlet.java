package com.web.searchlocal.servlet;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.web.searchlocal.bean.FileOpenerBean;
import com.web.searchlocal.bean.MessageBean;
import com.web.searchlocal.constants.Constant;
import com.web.searchlocal.factory.FileOpenerFactory;
import com.web.searchlocal.util.SessionUtil;
import com.web.searchlocal.util.StringUtil;
import com.web.searchlocal.util.WebMessageUtil;
import com.web.searchlocal.util.WinOpenFileUtil;

/**
 * 打开某个文件
 * 
 * <p>Title:点击打开文件</p>
 * <p>Description: DB的共通操作</p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class DoOpenFileServlet extends HttpServlet {

	/** serialVersionUID */
	private static final long serialVersionUID = 1L;
	
	private static WebMessageUtil msg = new WebMessageUtil();

	public DoOpenFileServlet() {
	}

	/**
	 * 打开某个文件
	 * 
	 * @param request
	 * @param response
	 * @throws ServletException
	 * @throws IOException
	 */
	protected void service(HttpServletRequest request,
			HttpServletResponse response) throws ServletException, IOException {

		// 文件路径
		String path = request.getParameter("path");  
		String attach = request.getParameter("attach");  
		
		HttpSession session = SessionUtil.getNewSession(request);
		String query = (String) session.getAttribute("query");
		
		// 打开文件
	    FileOpenerFactory.getFileOpeners();
	    
		String suffixName = StringUtil.suffixName(path);
		String opener = "";
		try{
			if (suffixName.equals(Constant.FileClassify.XLS) || suffixName.equals(Constant.FileClassify.XLS2007) ) {
				FileOpenerBean bean = FileOpenerFactory.getFileOpenerByType("excel");
				opener = bean.getExePath();
				String row = StringUtil.findNum(attach);
				String sheetName = StringUtil.findSheetName(attach);
				WinOpenFileUtil.openExcelFile(path, sheetName, row, query);
			}
			if (suffixName.equals(Constant.FileClassify.DOC) || suffixName.equals(Constant.FileClassify.DOC2007) ) {
				FileOpenerBean bean = FileOpenerFactory.getFileOpenerByType("word");
				opener = bean.getExePath();
				
				String page = StringUtil.findNum(attach);
				WinOpenFileUtil.openWordFile(path, page, query);
			}
			if (suffixName.equals(Constant.FileClassify.PPT) || suffixName.equals(Constant.FileClassify.PPT2007) ) {
				FileOpenerBean bean = FileOpenerFactory.getFileOpenerByType("ppt");
				opener = bean.getExePath();
				
				String page = StringUtil.findNum(attach);
				WinOpenFileUtil.openPPTFile(path, page, query);
			}
			if (suffixName.equals(Constant.FileClassify.PDF)) {
				FileOpenerBean bean = FileOpenerFactory.getFileOpenerByType("pdf");
				opener = bean.getExePath();
				String page = StringUtil.findNum(attach);
				// PDF采用命令行打开,所以必须那个转化
				path = "\"" + path + "\"";
				openPdfFile(opener, path, page);
			}
			if (Constant.FileClassify.isHtmlcontain(suffixName)) {
				FileOpenerBean bean = FileOpenerFactory.getFileOpenerByType("html");
				opener = bean.getExePath();
				// 打开IE文件
				path = "\"" + path + "\"";
				openFile(opener, path);
			}
			if (Constant.SrcClassify.iscontain(suffixName)) {
				FileOpenerBean bean = FileOpenerFactory.getFileOpenerByType("txt");
				opener = bean.getExePath();
				String row = StringUtil.findNum(attach);
				WinOpenFileUtil.openTxtFile(path, row, query);
			}
		}catch(Exception e){
			// 如果定位打开出现错误,则普通打开
			// 首尾加入引号,防止名称空格问题
			e.printStackTrace();
			path = "\"" + path + "\"";
			// 打开文件
			openFile(opener, path);
		}
	
		ServletContext sc = getServletContext();
		RequestDispatcher rd = null;
		// request.setAttribute(Constant.web_msg_list, msgList);

		rd = sc.getRequestDispatcher(Constant.WEB_RESULT_JSP);
		rd.forward(request, response);
	}
	
	/**
	 * 打开某个文件
	 * 
	 * @param path 文件路径
	 */
	protected void openFile(String opener, String path){
		// 消息
		List msgList = new ArrayList();
		try {
			System.out.println(opener + " " + path);
			Runtime.getRuntime().exec(opener + " " + path);
		} catch (IOException e) {
			MessageBean msgBean1 = new MessageBean(Constant.MsgCode.ERR, Constant.web_error_nosetopener, msg.getMsgbyId(Constant.web_error_nosetopener), null);
			msgList.add(msgBean1);
		}
	}
	
	/**
	 * 打开某个文件
	 * 
	 * @param path 文件路径
	 */
	protected void openPdfFile(String opener, String path, String page){
		// 消息
		List msgList = new ArrayList();
		try {
			System.out.println(opener + " " + path);
			Runtime.getRuntime().exec(opener + " " + "/a page=" + page + " " + path);
		} catch (IOException e) {
			MessageBean msgBean1 = new MessageBean(Constant.MsgCode.ERR, Constant.web_error_nosetopener, msg.getMsgbyId(Constant.web_error_nosetopener), null);
			msgList.add(msgBean1);
		}
	}
}
