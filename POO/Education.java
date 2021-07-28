import java.time.LocalDate;

class InvalidDatesException extends Exception {
	public InvalidDatesException(String mesaj) {
		super(mesaj);
	}
	//exceptia creata pentru cazul in care data de inceput este dupa data de sfarsit
}

class Education implements Comparable<Object> {
	public LocalDate start;
	public LocalDate end;
	public String institutioName;
	public String level;
	public Double avgGrade;
	
	public Education(LocalDate start, LocalDate end, String institutionName, String level, Double avgGrade) throws InvalidDatesException { 
		if(end != null && start.isAfter(end))
			throw new InvalidDatesException("Exceptie");
		
		this.start = start;
		this.end = end;
		this.avgGrade = avgGrade;
		this.level = level;
		this.institutioName = institutionName;
	}

	public int compareTo(Object o) {
		Education e = (Education) o;
		
		if(e.end == null)
			e.end = LocalDate.now();
		
		if(end == null) 
			end = LocalDate.now();
		
		if(e.end.compareTo(end) == 0)
			return e.avgGrade.compareTo(avgGrade);
		return e.end.compareTo(end);
		//functia compareTo pentru sortare descrescatoare in functie de data absolvirii
		//daca datele absolvirii coincid de face sortarea descrescator dupa media absolvirii
	}
}

class Experience implements Comparable<Object> {
	public LocalDate start;
	public LocalDate end;
	public String position;
	public String company;
	
	public Experience(LocalDate start, LocalDate end, String position, String company) throws InvalidDatesException {
		if(end != null && start.isAfter(end))
			throw new InvalidDatesException("Exceptie");
		
		this.start = start;
		this.end = end;
		this.position = position;
		this.company = company;
	}	

	public int compareTo(Object o) {
		Experience e = (Experience) o;
		
		if(e.end == null)
			e.end = LocalDate.now();
		
		if(end == null) 
			end = LocalDate.now();
		
		if(e.end.compareTo(end) == 0)
			return company.compareTo(e.company);
		return e.end.compareTo(end);
		//functia compareTo pentru sortare crescatoare in functie de data de sfarsit
		//daca datele absolvirii coincid de face sortarea crescator dupa nume
	}
}