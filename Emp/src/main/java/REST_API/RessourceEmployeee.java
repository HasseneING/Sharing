package REST_API;

import java.util.ArrayList;
import java.util.List;


import javax.ws.rs.Consumes;
import javax.ws.rs.DELETE;
import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.PUT;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;


@Path("employes")
public class RessourceEmployeee {


static List<Employee> employes = new ArrayList<Employee>();



@POST
@Consumes(MediaType.APPLICATION_XML)
@Produces(MediaType.TEXT_PLAIN)
public String AjouterEmployee(Employee e)
{
if (employes.add(e))
return "Employe ajoute";
else
return "Employe non ajoute";
}



@GET

//@Produces("application/xml")
@Produces(MediaType.APPLICATION_JSON)
public List<Employee> afficherListeEmployes() {
if (employes==null) 
return null;
return employes;
}


@GET
@Path("{cin}")
@Produces("application/xml")
public Employee chercherEmploye(@PathParam("cin") String cin) {
int index = this.getIndexByCin(cin);
if (index != -1) {
return employes.get(index);
}
return null;
}

@PUT
@Consumes(MediaType.APPLICATION_XML)
public String updateEmploye(Employee e) {
int index= getIndexByCin(e.getCin());
if (index!=-1) {
employes.set(index, e);
return "update successful";
}
return "update unsuccessful";
}

@DELETE
@Path("{c}")
@Produces(MediaType.TEXT_PLAIN)
public String deleteEmploye(@PathParam("c") String cin) {
int index= getIndexByCin(cin);
if (index!=-1) {

employes.remove(index);
return "true";
}else 
return "false";
}

public int getIndexByCin(String cin) {
for(Employee emp: employes) {
if (emp.getCin().equals(cin))
return employes.indexOf(emp);
}
return -1;
}


}