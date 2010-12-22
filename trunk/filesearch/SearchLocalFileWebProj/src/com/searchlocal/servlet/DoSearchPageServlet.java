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

/**
 * 
 * @version $Revision$
 */
public class DoSearchPageServlet extends HttpServlet {

	/** serialVersionUID */
	private static final long serialVersionUID = 1L;

	/** WEB_INDEX_JSP */
	private static final String WEB_INDEX_JSP = "/webapp/web/result.jsp";

	/** ENCODE_UTF_8 */
	private static final String ENCODE_UTF_8 = "utf-8";


	public DoSearchPageServlet() {
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
		// get query from session
		String query = (String) session.getAttribute("query");

		// TODO
		String searchname = (String) session.getAttribute("searchname");
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
		param.setSearchname(searchname);
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
