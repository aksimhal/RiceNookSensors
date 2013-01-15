//Displays data from a python POST script
//1-14-13

package guestbook;
import java.io.IOException;

import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.google.appengine.api.datastore.DatastoreService;
import com.google.appengine.api.datastore.DatastoreServiceFactory;
import com.google.appengine.api.datastore.Entity;
import com.google.appengine.api.datastore.PreparedQuery;
import com.google.appengine.api.datastore.Query;

@SuppressWarnings("serial")
public class GuestbookServlet extends HttpServlet {
	public void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
		resp.setContentType("text/plain");
		resp.getWriter().println("Welcome to Rice Hall \nBelow are a list of available nooks");
		
		Entity e = getFromDatabase("id");
		if(e != null) {
			resp.getWriter().println(e.getProperty("id"));
		}
		//System.out.println("failed to find ");
		
		System.out.println();
	}
	
	public void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException {
		resp.setContentType("text/plain"); //response object is output, req is input 
		resp.getWriter().println("Hello alex");

		DatastoreService ds = DatastoreServiceFactory.getDatastoreService();
		String userId = (String) req.getParameter("id"); //this is the input from the python code 
		
		Entity e = getFromDatabase("id");
		
		
		if(e != null) {
			e.setProperty("id", userId);
			ds.put(e);
		}
		else {
			Entity postEntity = new Entity("data");
			postEntity.setProperty("id", userId);
			ds.put(postEntity);
		}
		 
		System.out.println("doPost()");
	}
	
	public Entity getFromDatabase(String id) {
		System.out.println("in getFromDatabase");
		Query q = new Query("data");
		DatastoreService ds = DatastoreServiceFactory.getDatastoreService();
		PreparedQuery pq = ds.prepare(q);
		for(Entity e : pq.asIterable()) {
			System.out.println("found "+e.getProperty("id"));
			//resp.getWriter().println("found "+e.getProperty("id")); 
			return e;
		}
		return null;
	}
}

