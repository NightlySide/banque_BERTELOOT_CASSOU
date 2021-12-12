void ouvrir(FILE *f, char nom[]){
  const char* extension = ".dat";
  char* name_with_extension;
  name_with_extension = malloc(strlen(nom)+1+4); /* make space for the new string (should check the return value ...) */
  strcpy(name_with_extension, nom); /* copy name into the new var */
  strcat(name_with_extension, extension); /* add the extension */
  f = fopen(name_with_extension ,"a");
}


void fermer(FILE *f)
{
  fclose(f);
}

