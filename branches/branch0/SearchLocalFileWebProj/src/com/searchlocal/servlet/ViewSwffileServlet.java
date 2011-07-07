package com.searchlocal.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.searchlocal.constants.Constant;
import com.searchlocal.param.CreateNewParam;
import com.searchlocal.util.SessionUtil;
import com.searchlocal.util.XMLConfig;

/**
 * 
 * @version $Revision$
 */
public class ViewSwffileServlet extends HttpServlet {

	/** serialVersionUID */
	private static final long serialVersionUID = 1L;

	public ViewSwffileServlet() {
	}

	/**
	 * 生成SWF文件
	 * 
	 * @param request
	 * @param response
	 * 
	 * @throws ServletException
	 * @throws IOException
	 */
	protected void service(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		// SWF文件
		String swffile = request.getParameter("swffile");

		HttpSession session = SessionUtil.getNewSession(request);
		session.setAttribute("swffile", swffile);
		
		String json = json(swffile);
		writeJsonDatas(response, json);
	}
	
	/**
	 * 返回数据更新失败信息
	 *
	 * @return 
	 */
	public static String json(String swffile){
		return "{swffile:'"+swffile+"'}";
	}
	

	/**
	 * 正常情况下json输出
	 * 
	 * @param response 
	 * @param json 数据
	 * @throws IOException 
	 */
	protected void writeJsonDatas(HttpServletResponse response, String json) throws IOException {
		// 处理中文问题
		response.setCharacterEncoding("UTF-8");
		PrintWriter out = response.getWriter();
		out.write(json);
		out.close();
	}
}
