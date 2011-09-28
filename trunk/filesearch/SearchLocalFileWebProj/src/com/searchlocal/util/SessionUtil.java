package com.web.searchlocal.util;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

public class SessionUtil {

	public SessionUtil() {
		super();
		// TODO Auto-generated constructor stub
	}

	public static HttpSession getNewSession(HttpServletRequest req) {
		HttpSession session = req.getSession(true);
		return session;
	}
}
