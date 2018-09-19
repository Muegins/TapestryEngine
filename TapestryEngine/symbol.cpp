#include "symbol.h"

int ConvertStringToSymbol(char * str)
{

	     if (!strcmp(str, "IDLE")				) { return IDLE;				}
	else if (!strcmp(str, "IDLE_DRAWN")			) { return IDLE_DRAWN;			}
	else if (!strcmp(str, "RUN")				) { return RUN;					}
	else if (!strcmp(str, "RUN_DRAWN")			) { return RUN_DRAWN;			}
	else if (!strcmp(str, "JUMP")				) { return JUMP;				}
	else if (!strcmp(str, "JUMP_DRAWN")			) { return JUMP_DRAWN;			}
	else if (!strcmp(str, "JUMP_TO_FALL")		) { return JUMP_TO_FALL;		}
	else if (!strcmp(str, "JUMP_TO_FALL_DRAWN")	) { return JUMP_TO_FALL_DRAWN;	}
	else if (!strcmp(str, "FALL")				) { return FALL;				}
	else if (!strcmp(str, "FALL_DRAWN")			) { return FALL_DRAWN;			}
	else if (!strcmp(str, "IDLE_BEGIN")			) { return IDLE_BEGIN;			}
	else if (!strcmp(str, "IDLE_BEGIN_DRAWN")	) { return IDLE_BEGIN_DRAWN;	}
	else if (!strcmp(str, "SWIM")				) { return SWIM;				}
	else if (!strcmp(str, "SWIM_BEGIN")			) { return SWIM_BEGIN;			}
	else if (!strcmp(str, "TREAD")				) { return TREAD;				}
	else if (!strcmp(str, "DIE")				) { return DIE;					}
	else if (!strcmp(str, "DEAD")				) { return DEAD;				}
	else if (!strcmp(str, "ATTACK")				) { return ATTACK;				}
	else if (!strcmp(str, "LOOK")				) { return LOOK;				}	 
	else if (!strcmp(str, "EAT")				) { return EAT;					}
	else if (!strcmp(str, "SLEEP")				) { return SLEEP;				}
	else if (!strcmp(str, "PARTICLE")			) { return PARTICLE;			}
	else if (!strcmp(str, "SPLASH")				) { return SPLASH;				}
	else if (!strcmp(str, "HAZE")				) { return HAZE;				}
	else if (!strcmp(str, "GATE_UP")			) { return GATE_UP;				}
	else if (!strcmp(str, "GATE_DOWN")			) { return GATE_DOWN;			}
	else if (!strcmp(str, "GATE_LOWER")			) { return GATE_LOWER;			}
	else if (!strcmp(str, "GATE_LOWER_BEGIN")	) { return GATE_LOWER_BEGIN;	}
	else if (!strcmp(str, "GATE_RAISE")			) { return GATE_RAISE;			}
	else if (!strcmp(str, "LEFT")				) { return LEFT;				}
	else if (!strcmp(str, "RIGHT")				) { return RIGHT;				}
	else if (!strcmp(str, "NONE")				) { return -1;					}
	else
	{
		gCons->ConsPrintf("%s : unrecognized string\n", str);
		return NULL;
	}
}