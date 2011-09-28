package com.web.searchlocal.servlet;

import java.io.IOException;
import java.util.List;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.web.searchlocal.constants.Constant;
import com.web.searchlocal.entity.PageEntity;
import com.web.searchlocal.exception.LogicException;
import com.web.searchlocal.param.SearchParam;
import com.web.searchlocal.service.SearchService;
import com.web.searchlocal.service.impl.SearchServiceImpl;
import com.web.searchlocal.util.PagerHelper;
import com.web.searchlocal.util.SessionUtil;

/**
 * 
 * @version $Revision$
 */
public class DoSearchPageServlet extends HttpServlet {

	/** serialVersionUID */
	private static final long serialVersionUID = 1L;

	public DoSearchPageServlet() {
	}

	/**
	 * 
	 * 
	 * @param request
	 * @param response
	 * @throws ServletException
	 * @throws IOException
	 */
	protected void service(HttpServletRequest request,
			HttpServletResponse response) throws ServletException, IOException {

		HttpSession session = SessionUtil.getNewSession(request);
		// get query from session
		String query = (String) session.getAttribute("query");

		// TODO
		String id = (String) session.getAttribute("id");
		String searchtype = (String) session.getAttribute("searchtype");

		PageEntity spageEntity = (PageEntity) session
				.getAttribute("pageEntity");

		String pageNo = request.getParameter("pageNo");
		String pagerMethod = request.getParameter("pageMethod");
		String currentPage = null;
		if (pageNo != null) {
			request.setAttribute("cpageNo", pageNo);
			currentPage = pageNo;
		} else {
			currentPage = (String) request.getParameter("cpageNo");
		}

		PageEntity pageEntity = PagerHelper.getPager(currentPage, pageNo,
				pagerMethod, spageEntity.getTotalRows());

		if (pageNo == null) {
			request.setAttribute("cpageNo", String.valueOf(pageEntity
					.getCurrentPage()));
		}

		SearchParam param = new SearchParam();
		param.setQuery(query);
		param.setId(id);
		param.setSearchtype(searchtype);

		// get count of search
		SearchService searchService = new SearchServiceImpl();
		param.setStartRow(pageEntity.getStartRow());
		param.setEndRow(pageEntity.getEndRow());
		List beanList = null;
		
		try{
		    beanList = searchService.dosearcher(param);
		} catch (LogicException e) {
			session.setAttribute(Constant.web_error_noresult, e.getMessage());
		}

		session.setAttribute("pageEntity", pageEntity);
		session.setAttribute("query", query);
		session.setAttribute("beanList", beanList);
		ServletContext sc = getServletContext();
		RequestDispatcher rd = sc.getRequestDispatcher(Constant.WEB_RESULT_JSP);
		rd.forward(request, response);
	}
}
