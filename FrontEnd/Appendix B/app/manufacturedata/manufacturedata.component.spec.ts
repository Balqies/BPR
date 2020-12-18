import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ManufacturedataComponent } from './manufacturedata.component';

describe('ManufacturedataComponent', () => {
  let component: ManufacturedataComponent;
  let fixture: ComponentFixture<ManufacturedataComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ManufacturedataComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(ManufacturedataComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
