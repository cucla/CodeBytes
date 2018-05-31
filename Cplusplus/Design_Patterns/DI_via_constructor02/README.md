Dependency Injection via constructor with Interfaces<br/>
PROS:
<ul>
  <li>Hide implementation details in the .cpp files</li>
  <li>Work against abstract interfaces</li>
  <li>Inject dependencies during object construction</li>
</ul>
Contents:
<ul>
  <li>IDependency.h - interface for an object to be injected</li>
  <li>DepImpl1.cpp</li>
  <li>DepImpl2.cpp</li>
  <li>IA.h - class having 'IDependency' object as a unique_ptr; divided into interface and .cpp file</li>
  <li>A.cpp</li>
  <li>B.h - class having 'IDependency' object as a shared_ptr; not divided into interface</li>
  <li>PrimerExample.cpp - main function</li>
  <li>Test.cpp</li>
</ul>
