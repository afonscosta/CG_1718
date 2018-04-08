# Notas
1. Substitui os itálicos para latex
	%s/\*\(.\{-}\)\*/\\textit{\1}/gc
1. Substitui os negritos para latex
	%s/\*\*\(.\{-\}\)\*\*/\\textbf{\1}/gc

2. Data structure diagram

# Carregamento do XML
- Que biblioteca é usada (Pugixml) 											[X]
- Vantagens de ter a estrutura de dados em vez de ler sempre do ficheiro. 	[X]
- Estrutura de dados usada para armazenar a info. 							[X]
- Como é feito? Iteradores + atof											[ ]
- Quando é que é feito?														[ ]

# Carregamento do XML
O *engine* é um componente responsável por concretizar efetivamente a cena. No entanto, fá-lo com completa abstração quanto àquilo que está a desenhar. Desta forma, é o próprio ficheiro XML passado por argumento ao *engine* que é responsável por organizar a cena e estruturar todas as suas primitivas de forma a produzir o resultado desejável.

Assim sendo, é necessário carregar o conteúdo do ficheiro XML havendo para o efeito duas abordagens possíveis, fazer *parse* deste documento todas as vezes que fosse necessário redesenhar a cena ou apenas fazer *parse* do ficheiro uma vez, carregar os dados para uma estrutura de dados e redesenhar a cena com base nesta. A abordagem escolhida foi a segunda visto que o acesso a ficheiros é inevitavelmente uma operação muito custosa que iria ser repetida um número elevadíssimo de vezes. Assim, o *parse* do ficheiro é apenas realizado uma vez e, posteriormente, quando for necessário o acesso à informação da cena, este é realizado diretamente à estrutura de dados criada para o efeito. No caso concreto deste projeto, o carregamento do XML é realizado através da biblioteca *Pugixml*.

%[TEMPOS DE ACESSO AOS DADOS ANTES E DEPOIS DO UPGRADE]

Deste modo, foi criada uma estrutura de dados capaz de armazenar os dados presentes no ficheiro XML. Esta teria de conter um **group**, que por sua vez conteria um **translate**, **rotate**, **scale**, **models**, e novamente um **group**. Ainda, o elemento **models** pode conter um ou mais **model**. Todos este componentes são no entanto opcionais e como tal nem todos precisam de estar sempre presentes. De forma a auxiliar a representação do um ponto genérico, ou seja, constituído por uma coordenada x, y e z, foi criada uma classe Point que representa exatamente esse modelo de dados. Assim sendo, dentro da classe **Group** existe um **Point translate**, que armazena as coordenadas necessárias à realização *translate*, existe um **float angle** que juntamente com um **Point rotate** permitem executar rotações aos modelos do grupo em questão, existe um **vector<Model> models** que permite armazenar todos os modelos presente neste elemento, a classe **Model** por sua vez representa todos os pontos da primitiva expressa em cada um dos ficheiros 3d e como tal apenas tem como variável um **vector<Point> primitive**, ou seja, um vetor com todos os pontos necessários para desenhar determinada figura. Por fim, a classe **Group** contém um **vector<Group *> groups** que fica responsável por agrupar num vetor com os apontadores para todos os grupos que um determinado grupo possa integrar, surgindo desta forma recursividade no tipo de dados. 

[DIAGRAMA COM A ESTRUTURA DE DADOS]

- Como é feito? Iteradores + atof











# Construção da cena
- Como é desenhada? drawGroup + PushMatrix + PopMatrix
- Quando é desenhada? PostRedisplay...


