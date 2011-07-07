package com.searchlocal.servlet;

import java.io.IOException;
import java.util.List;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.searchlocal.constants.Constant;
import com.searchlocal.entity.PageEntity;
import com.searchlocal.exception.LogicException;
import com.searchlocal.param.SearchParam;
import com.searchlocal.service.SearchService;
import com.searchlocal.service.impl.SearchServiceImpl;
import com.searchlocal.util.PagerHelper;
import com.searchlocal.util.SessionUtil;
import com.searchlocal.util.StringUtil;

/**
 * 
 * @version $Revision$
 */
public class DoSearchServlet extends HttpServlet {

	/** serialVersionUID */
	private static final long serialVersionUID = 1L;

	public DoSearchServlet() {
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

		// query
		String query = request.getParameter("query");

		HttpSession session = SessionUtil.getNewSession(request);
		String searchtype = (String) session.getAttribute("searchtype");
		
		if(StringUtil.isNullString(searchtype)){
			searchtype = "all";
		}

		String searchname = (String) request.getParameter("searchname");
		if (null == searchname) {
			searchname = (String) session.getAttribute("searchname");
		}

		session.removeAttribute("pageEntity");

		SearchParam param = new SearchParam();
		param.setQuery(query);
		param.setSearchname(searchname);
		param.setSearchtype(searchtype);

		// get count of search
		SearchService searchService = new SearchServiceImpl();
		int totalRows = searchService.getCount(param);
		PageEntity pageEntity = PagerHelper.getPager(null, null, null,totalRows);

		param.setStartRow(pageEntity.getStartRow());
		param.setEndRow(pageEntity.getEndRow());
		List beanList = null;
		try {
			beanList = searchService.dosearcher(param);
		} catch (LogicException e) {
			session.setAttribute(Constant.web_error_noresult, e.getMessage());
		}

		session.setAttribute("pageEntity", pageEntity);
		session.setAttribute("query", query);
		session.setAttribute("searchname", searchname);
		session.setAttribute("beanList", beanList);
		request.setAttribute("cpageNo", "1");

		ServletContext sc = getServletContext();
		RequestDispatcher rd = sc.getRequestDispatcher(Constant.WEB_RESULT_JSP);
		rd.forward(request, response);
	}
}
