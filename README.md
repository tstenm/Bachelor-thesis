Github Repository meiner Bacheloarbeit mit dem Titel "Erweiterung der planungsbasierten Ressourcenverwaltung zur Unterstützung von Hugepages für HPC-Systeme".
In diesem Github Repo befinden sich : Ein modifizierter Kernel (mmap-autoselect), ein unmodifizierter Kernel, Helfer-Programme, Messergebnisse und Testprogramme.

Es ist wichtig zu beachten, dass beim Test des Kernels ausreichend Hugepages vorab reserviert werden. 
PUD-Pages im laufenden Betrieb zu allokieren ging mit Schwierigikeiten einher, weshalb diese beim Boot allokiert werden.
PMD-Pages können problemlos im laufenden Betrieb allokiert werden : n > /sys/kernel/mm/hugepages/hugepage-2048kB/nr_hugepages
n ist die Anzahl der Hugepages. 



