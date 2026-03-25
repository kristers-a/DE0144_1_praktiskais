# DE0144 1. praktiskais darbs

Spēles apraksts
-----------------

Spēles sākumā cilvēks-spēlētājs norāda spēlē izmantojamas simbolu virknes garumu, kas var būt diapazonā no 15 līdz 25 simboliem. Spēles programmatūra gadījuma ceļā saģenerē simbolu virkni atbilstoši uzdotajam garumam, tajā iekļaujot X un O simbolus. Spēles apraksts Spēles sākumā ir dota ģenerētā simbolu virkne. Katram spēlētajam ir 0 punktu. Viens spēlētājs spēlē ar apļiem, otrs – ar krustiņiem. Spēli uzsāk spēlētājs, kas spēlē ar aplīšiem. Spēlētājs ar aplīšiem drīkst aizvietot divus blakusstāvošus krustiņus ar aplīti (XX=O) un par to iegūt 2 punktus sev, vai krustiņu un aplīti, kas stāv blakus, ar aplīti (XO=O) un atņemt 1 punktu no pretinieka punktu skaita. Spēlētājs ar krustiņiem līdzīgi drīkst aizvietot divus aplīšus ar krustiņu (OO=X) un par to iegūt 2 punktu sev un aplīti un krustiņu ar krustiņu (OX=X) un atņemt vienu punktu no pretinieka punktu skaita. Spēle beidzas, kad kāds no spēlētājiem nevar izdarīt gājienu, vai simbolu virknē ir palikusi tikai viena figūra. Uzvar spēlētājs, kam spēles beigās ir vairāk punktu.

Papildus informācija
-----------------
Spēlē spēlētājs var izvēlēties vai vēlās spēlēt ar krustiņiem vai aplīšiem, un kuru no algorimiem vēlās izmantot (Mini-Max, Alfa-Beta).
Spēli ir ieteicams spēlēt ar pārmeklēšanas dziļumu - 6, ko var nomainīt iekš Form1.cpp.

Spēle ir taisīta iekš C++ valodas ar C++ Windows Forms for VS 2022 .NET Framework:

[https://marketplace.visualstudio.com/items?itemName=RichardKaiser.cppclrwinf](https://marketplace.visualstudio.com/items?itemName=RichardKaiser.cppclrwinf)
