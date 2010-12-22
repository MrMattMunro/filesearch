package com.searchlocal.servlet;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.searchlocal.bean.MessageBean;
import com.searchlocal.constants.Constant;
import com.searchlocal.util.ConstantExeFileUtil;
import com.searchlocal.util.StringUtil;
import com.searchlocal.util.WebMessageUtil;

/**
 * 
 * @version $Revision$
 */
public class DoOpenFileServlet extends HttpServlet {

	/** serialVersionUID */
	private static final long serialVersionUID = 1L;
	
	private static WebMessageUtil msg = new WebMessageUtil();

	public DoOpenFileServlet() {
	}

	/**
	 * 
	 * @param request
	 * @param response
	 * 
	 * @throws ServletException
	 * @throws IOException
	 */
	protected void service(HttpServletRequest request,
			HttpServletResponse response) throws ServletException, IOException {
		
		List msgList = new ArrayList();
		
		ConstantExeFileUtil.readFile();
		String path = request.getParameter("path");        
		String suffixName = StringUtil.suffixName(path);

		String opener = "";
		if (suffixName.equals(Constant.FileClassify.XLS) || suffixName.equals(Constant.FileClassify.XLS2007) ) {
			opener = ConstantExeFileUtil.getOpenerbyId("excel");
		}
		if (suffixName.equals(Constant.FileClassify.DOC) || suffixName.equals(Constant.FileClassify.DOC2007) ) {
			opener = ConstantExeFileUtil.getOpenerbyId("word");
		}
		if (suffixName.equals(Constant.FileClassify.PPT) || suffixName.equals(Constant.FileClassify.PPT2007) ) {
			opener = ConstantExeFileUtil.getOpenerbyId("ppt");
		}
		if (suffixName.equals(Constant.FileClassify.PDF)) {
			opener = ConstantExeFileUtil.getOpenerbyId("pdf");
		}
		if (Constant.FileClassify.isHtmlcontain(suffixName)) {
			opener = ConstantExeFileUtil.getOpenerbyId("ie");
		}
		if (Constant.SrcClassify.iscontain(suffixName)) {
			opener = ConstantExeFileUtil.getOpenerbyId("txt");
		}
		
		ServletContext sc = getServletContext();
		RequestDispatcher rd = null;
		try {
			Runtime.getRuntime().exec(opener + " " + path);
		} catch (IOException e) {
			MessageBean msgBean1 = new MessageBean(Constant.MsgCode.ERR, Constant.web_error_nosetopener, msg.getMsgbyId(Constant.web_error_nosetopener), null);
			msgList.add(msgBean1);
			request.setAttribute(Constant.web_msg_list, msgList);
		}

		rd = sc.getRequestDispatcher(Constant.WEB_RESULT_JSP);
		rd.forward(request, response);
	}
}
