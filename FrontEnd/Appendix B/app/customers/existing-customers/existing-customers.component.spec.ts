import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ExistingCustomersComponent } from './existing-customers.component';

describe('ExistingCustomersComponent', () => {
  let component: ExistingCustomersComponent;
  let fixture: ComponentFixture<ExistingCustomersComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ExistingCustomersComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(ExistingCustomersComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
