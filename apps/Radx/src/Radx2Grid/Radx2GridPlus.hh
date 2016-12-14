#ifndef Radx2GridPlus_hh
#define Radx2GridPlus_hh

typedef enum {
  REF = 0,
  VEL = 1,
  SW = 2,
  ZDR = 3,
  RHO = 4,
  PHI = 5,
  KDP = 6,
  U = 7,
  V = 8,
  W = 9,
}fields_t;


class Radx2GridPlus{

	private: 
		string _program_name;
		List<int> _fields;
		int _no_of_fields;
		
	public: 
		void processFile(string filename);
		void mapping_field_names(select_field_t * selected_fields);
}

#endif
