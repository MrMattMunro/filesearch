package com.searchlocal.servlet;

import java.io.IOException;
import java.util.Iterator;
import java.util.List;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.searchlocal.constants.Constant;
import com.searchlocal.param.CreateNewParam;
import com.searchlocal.util.SessionUtil;

/**
 * 
 * @version $Revision$
 */
public class DoChangeSearchServlet extends HttpServlet {

	/** serialVersionUID */
	private static final long serialVersionUID = 1L;


	public DoChangeSearchServlet() {
	}

	/**
	 * 
	 * 
	 * 
	 * @param request
	 * @param response
	 * 
	 * @throws ServletException
	 * @throws IOException
	 */
	protected void service(HttpServletRequest request,
			HttpServletResponse response) throws ServletException, IOException {

		HttpSession session = SessionUtil.getNewSession(request);
		session.setAttribute("searchtype", "all");

		String searchname = request.getParameter("searchname");

		List entityList = (List) session.getAttribute("entityList");
		for (Iterator iter = entityList.iterator(); iter.hasNext();) {
			CreateNewParam element = (CreateNewParam) iter.next();
			if (searchname.equals(element.getSearchname())) {
				element.setSearchname(element.getSearchname());
				element.setPath(element.getPath());
				session.setAttribute("element", element);
			}
		}

		session.setAttribute("searchname", searchname);
		ServletContext sc = getServletContext();
		RequestDispatcher rd = sc.getRequestDispatcher(Constant.WEB_INDEX_JSP);
		rd.forward(request, response);
	}
}
