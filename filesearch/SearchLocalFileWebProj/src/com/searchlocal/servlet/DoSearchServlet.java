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
import com.web.searchlocal.util.StringUtil;

/**
 * 检索索引文件
 * 
 * <p>Title: 检索索引文件</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class DoSearchServlet extends HttpServlet {

	/** serialVersionUID */
	private static final long serialVersionUID = 1L;

	/**
	 * 构造器
	 */
	public DoSearchServlet() {
	}

	/**
	 * 根据关键字检索
	 * 
	 * @param request
	 * @param response
	 * @throws ServletException
	 * @throws IOException
	 */
	protected void service(HttpServletRequest request,
			HttpServletResponse response) throws ServletException, IOException {

		// query
		String query = request.getParameter("query");

		HttpSession session = SessionUtil.getNewSession(request);
		String searchtype = (String) session.getAttribute("searchtype");
		
		// 检索全部
		if(StringUtil.isNullString(searchtype)){
			searchtype = Constant.ALL;
		}

		// 搜索名称
		String id = (String) request.getParameter("id");
		if (null == id) {
			id = (String) session.getAttribute("id");
		}

		session.removeAttribute("pageEntity");

		// 设置参数
		SearchParam param = new SearchParam();
		// 关键字
		param.setQuery(query);
		// 检索名
		param.setId(id);
		param.setSearchtype(searchtype);

		// 取得检索结果条数
		SearchService searchService = new SearchServiceImpl();
		int totalRows = 0;
		try {
			totalRows = searchService.getCount(param);
		} catch (LogicException e1) {
			e1.printStackTrace();
		}
		PageEntity pageEntity = PagerHelper.getPager(null, null, null, totalRows);

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
		session.setAttribute("id", id);
		session.setAttribute("beanList", beanList);
		request.setAttribute("cpageNo", "1");

		ServletContext sc = getServletContext();
		RequestDispatcher rd = sc.getRequestDispatcher(Constant.WEB_RESULT_JSP);
		rd.forward(request, response);
	}
}
