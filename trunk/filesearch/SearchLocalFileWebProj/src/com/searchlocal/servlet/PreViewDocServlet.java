package com.web.searchlocal.servlet;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.web.searchlocal.flashpaper.FileConvert;
import com.web.searchlocal.flashpaper.impl.FileConvert4SwfImpl;
import com.web.searchlocal.util.StringUtil;

/**
 * 
 * @version $Revision$
 */
public class PreViewDocServlet extends HttpServlet {

	/** serialVersionUID */
	private static final long serialVersionUID = 1L;

	public PreViewDocServlet() {
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
		// 文件
		String filepath = request.getParameter("filepath");
		
		// 用户所按的链接的坐标
		String index = request.getParameter("index");

		filepath = StringUtil.reconvertPath(filepath);
		
		// 生成swf路径  eg:D:/javahome/Tomcat5.5/webapps/slfile/
		String swfFilePaths  = getServletContext().getRealPath(""); 
		
		// 生成文件名
		// String swffile = Doc2Flash.convert2Flash(filepath, swfFilePaths);
		File inputFileInst = new File(filepath);
		File outputFileInst = new File(swfFilePaths);
		FileConvert fc = new FileConvert4SwfImpl();
		fc.doConvertFile(inputFileInst, outputFileInst);
		
	   String swffile = swfFilePaths + File.separator + inputFileInst.getName();
		String json = json(swffile, index, filepath);
		writeJsonDatas(response, json);
	}
	
	/**
	 * 返回数据更新失败信息
	 *
	 * @return 
	 */
	public static String json(String swffile, String index, String filepath){
		return "{swffile:'"+swffile+"',index:'"+index+"',filepath:'"+filepath+"'}";
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
		response.setCharacterEncoding("utf-8");
		
		PrintWriter out = response.getWriter();
		out.write(json);
		out.close();
	}
}
