# Project-Info

Dépendances :
-GNU Scientific Library (gsl) : http://ftp.igh.cnrs.fr/pub/gnu/gsl/

  INSTALLATION DE GSL :
  -Téléchargez la dernière version.
  -Dans le répertoire de gsl extrait :

    ./configure && make && make check && make install

    cd

    sudo gedit .bashrc

      A la fin du fichier ajouter :
        LD_LIBRARY_PATH=/usr/local/lib
        export LD_LIBRARY_PATH

  COMPILATION, LANCEMENT :
  -Dans le répertoire Code :

    make clean

    make

    ./TryToSurvive
