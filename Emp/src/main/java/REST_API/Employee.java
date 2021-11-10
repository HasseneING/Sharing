package REST_API;

import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;


@XmlRootElement 
public class Employee {

private String cin;
private String nom;
private String prenom;


public Employee() {
super();
// TODO Auto-generated constructor stub
}
public Employee(String cin, String nom, String prenom) {
super();
this.cin = cin;
this.nom = nom;
this.prenom = prenom;
}

@XmlAttribute(name="id") 
public String getCin() {
return cin;
}
public void setCin(String cin) {
this.cin = cin;
}

@XmlElement(name="FirstName")
public String getNom() {
return nom;
}
public void setNom(String nom) {
this.nom = nom;
}

@XmlElement(name="LasttName")
public String getPrenom() {
return prenom;
}
public void setPrenom(String prenom) {
this.prenom = prenom;
}
@Override
public int hashCode() {
final int prime = 31;
int result = 1;
result = prime * result + ((cin == null) ? 0 : cin.hashCode());
result = prime * result + ((nom == null) ? 0 : nom.hashCode());
result = prime * result + ((prenom == null) ? 0 : prenom.hashCode());
return result;
}
@Override
public boolean equals(Object obj) {
if (this == obj)
return true;
if (obj == null)
return false;
if (getClass() != obj.getClass())
return false;
Employee other = (Employee) obj;
if (cin == null) {
if (other.cin != null)
return false;
} else if (!cin.equals(other.cin))
return false;
if (nom == null) {
if (other.nom != null)
return false;
} else if (!nom.equals(other.nom))
return false;
if (prenom == null) {
if (other.prenom != null)
return false;
} else if (!prenom.equals(other.prenom))
return false;
return true;
}




}