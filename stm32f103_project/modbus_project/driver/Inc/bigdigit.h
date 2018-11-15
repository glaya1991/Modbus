# define _rdBYofW( _B, _W )   (((TVar(U8) *) &  _W)[_B])
# define _rdBYofDW( _B, _DW ) (((TVar(U8) *) & _DW)[_B])
# define _rdWofDW( _W, _DW )  (((TVar(U16)*) & _DW)[_W])

# define _wrBYofW( _B, _W )   (((TVar(U8)*)  &  _W)[_B])
# define _wrBYofDW( _B, _DW ) (((TVar(U8)*)  & _DW)[_B])
# define _wrWofDW( _W, _DW )  (((TVar(U16)*) & _DW)[_W])
