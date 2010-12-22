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
import com.searchlocal.param.CreateNewParam;
import com.searchlocal.util.SessionUtil;
import com.searchlocal.util.WebMessageUtil;
import com.searchlocal.util.XMLConfig;

/**
 * 
 * @version $Revision$
 */
public class LoadDataServlet extends HttpServlet {

	/** serialVersionUID */
	private static final long serialVersionUID = 1L;

	private static WebMessageUtil msg = new WebMessageUtil();

	public LoadDataServlet() {
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

		List entityList = XMLConfig.getList();
		CreateNewParam element = new CreateNewParam();
		session.setAttribute(Constant.is_no_search, Boolean.FALSE);
		if (entityList.size() > 0) {
			element = (CreateNewParam) entityList.get(0);
			element.setSearchname(element.getSearchname());
			element.setPath(element.getPath());
		} else {
			session.setAttribute(Constant.is_no_search, Boolean.TRUE);
		}

		session.setAttribute("entityList", entityList);
		session.setAttribute("element", element);
		session.setAttribute("searchtype", "all");

		// menu
		session.setAttribute(Constant.web_searchname, msg
				.getMsgbyId(Constant.web_searchname));
		session.setAttribute(Constant.web_searchpath, msg
				.getMsgbyId(Constant.web_searchpath));
		session.setAttribute(Constant.web_changesearch, msg
				.getMsgbyId(Constant.web_changesearch));
		session.setAttribute(Constant.web_allsearchtype, msg
				.getMsgbyId(Constant.web_allsearchtype));
		session.setAttribute(Constant.web_webpage, msg
				.getMsgbyId(Constant.web_webpage));
		session.setAttribute(Constant.web_source, msg
				.getMsgbyId(Constant.web_source));
		session.setAttribute(Constant.web_button, msg
				.getMsgbyId(Constant.web_button));
		session.setAttribute(Constant.web_returnhome, msg
				.getMsgbyId(Constant.web_returnhome));
		session.setAttribute(Constant.web_at, msg.getMsgbyId(Constant.web_at));
		session.setAttribute(Constant.web_findfile, msg
				.getMsgbyId(Constant.web_findfile));
		session.setAttribute(Constant.web_rows, msg
				.getMsgbyId(Constant.web_rows));
		session
				.setAttribute(Constant.web_the, msg
						.getMsgbyId(Constant.web_the));
		session.setAttribute(Constant.web_photogragh, msg
				.getMsgbyId(Constant.web_photogragh));
		session.setAttribute(Constant.web_excel_the, msg
				.getMsgbyId(Constant.web_excel_the));
		session.setAttribute(Constant.web_excel_page, msg
				.getMsgbyId(Constant.web_excel_page));
		session
				.setAttribute(Constant.web_row, msg
						.getMsgbyId(Constant.web_row));
		session.setAttribute(Constant.web_page, msg
				.getMsgbyId(Constant.web_page));

		session.setAttribute(Constant.web_chapter, msg
				.getMsgbyId(Constant.web_chapter));

		session.setAttribute(Constant.web_previouspage, msg
				.getMsgbyId(Constant.web_previouspage));

		session.setAttribute(Constant.web_nextpage, msg
				.getMsgbyId(Constant.web_nextpage));
		session.setAttribute(Constant.web_preview, msg
				.getMsgbyId(Constant.web_preview));
		session.setAttribute(Constant.web_view, msg
				.getMsgbyId(Constant.web_view));
		session.setAttribute(Constant.web_innewwin, msg
				.getMsgbyId(Constant.web_innewwin));

		session.setAttribute(Constant.web_error_nosearcher, msg.getMsgbyId(Constant.web_error_nosearcher));
		session.setAttribute(Constant.web_info_loading, msg.getMsgbyId(Constant.web_info_loading));

		ServletContext sc = getServletContext();
		RequestDispatcher rd = sc.getRequestDispatcher(Constant.WEB_INDEX_JSP);
		rd.forward(request, response);
	}
}
