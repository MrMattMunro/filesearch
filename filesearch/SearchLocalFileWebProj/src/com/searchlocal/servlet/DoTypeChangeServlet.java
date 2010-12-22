package com.searchlocal.servlet;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.searchlocal.constants.Constant;
import com.searchlocal.util.SessionUtil;

/**
 * 
 * @version $Revision$
 */
public class DoTypeChangeServlet extends HttpServlet {

	/** serialVersionUID */
	private static final long serialVersionUID = 1L;

	public DoTypeChangeServlet() {
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

		String searchtype = request.getParameter("searchtype");

		HttpSession session = SessionUtil.getNewSession(request);
		session.setAttribute("searchtype", searchtype);

		ServletContext sc = getServletContext();
		RequestDispatcher rd = sc.getRequestDispatcher(Constant.WEB_INDEX_JSP);
		rd.forward(request, response);
	}

}
